#include "BuildingComponent.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "Characters/BaseCharacter.h"
#include "BuildingObject/Modular/BuildingCeiling.h"
#include "BuildingObject/Modular/BuildingCeilingTriangle.h"
#include "BuildingObject/Modular/BuildingFoundation.h"
#include "BuildingObject/Modular/BuildingFoundationTriangle.h"
#include "BuildingObject/Modular/BuildingRoof.h"
#include "BuildingObject/Modular/BuildingWall.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widgets/HUDWidget.h"
#include "Interface/IPlayer.h"
#include "DataTable/CustomDataTables.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CHelpers::GetClass(&BuildingWidgetClass, "/Game/Widgets/WB_HUD");
}


void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayerController = Cast<APlayerController>(GetOwner());
	CheckNull(OwnerPlayerController);

	TrytoCreateBuildingWidget();
	
}


void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!!BuildingObject)
	{
		FHitResult hitResult;
		BuildTraceResult(hitResult);

		if (Cast<ABaseBuildingObject>(hitResult.Actor)) // 다른 건축애셋에 linetrace됐을때
		{
			CheckDistance(hitResult.Location, Cast<ABaseBuildingObject>(hitResult.Actor));
		}
		else // 다른 건축애셋에 linetrace되지 않았을때
		{
			if (!!NewHitActor)
			{
				NewHitActor = nullptr;
				SocketTransform.Empty();
			}

			FRotator rotation = FRotator(BuildingObject->GetActorRotation().Pitch ,OwnerPlayerController->PlayerCameraManager->K2_GetActorRotation().Yaw, BuildingObject->GetActorRotation().Roll);
			SpawnTransform = UKismetMathLibrary::MakeTransform(hitResult.Location, rotation, FVector(1.f, 1.f, 1.05f));
		}
		
		bInRange = hitResult.bBlockingHit;
		if(bInRange)
			BuildingObject->SetActorTransform(SpawnTransform);
	}
}

void UBuildingComponent::BuildTraceResult(FHitResult& OutHitResult)
{
	FVector start, end;
	float LocationX, LocationY;
	OwnerPlayerController->GetMousePosition(LocationX, LocationY);

	FVector wolrdLocation, worldDirection;
	OwnerPlayerController->DeprojectScreenPositionToWorld(LocationX, LocationY, wolrdLocation, worldDirection);
	start = wolrdLocation;
	end = wolrdLocation + (worldDirection * 1000);

	TArray<AActor*> ignoreActor;
	ignoreActor.Add(BuildingObject);
	ignoreActor.Add(UGameplayStatics::GetPlayerCharacter(this, 0));
	ignoreActor.Add(OwnerPlayerController->PlayerCameraManager);
	

	UKismetSystemLibrary::LineTraceSingle
	(
		GetOwner(),
		start,
		end,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ignoreActor,
		EDrawDebugTrace::None,
		OutHitResult,
		true
	);
}

void UBuildingComponent::CheckDistance(FVector InHitLocation, ABaseBuildingObject* InHitActor)
{
	if (NewHitActor == nullptr)
	{
		NewHitActor = InHitActor;
		TArray<USceneComponent*> ceilingSockets;

		GetBuildTransform(NewHitActor, ceilingSockets);

		if (ceilingSockets.Num() < 1) // ceilingSockets배열이 null일때
		{
			FRotator rotation = FRotator(BuildingObject->GetActorRotation().Pitch, OwnerPlayerController->PlayerCameraManager->K2_GetActorRotation().Yaw, BuildingObject->GetActorRotation().Roll);
			SpawnTransform = UKismetMathLibrary::MakeTransform(InHitLocation, rotation, FVector(1.f, 1.f, 1.05f));
			return;
		}
		else
		{
			for (int i = 0; i < ceilingSockets.Num(); i++)
			{
				SocketTransform.Add(ceilingSockets[i]->GetComponentTransform());
			}
		}
	}
	else if (InHitActor != NewHitActor) // 라인트레이싱이 히트중인 상태에서 새로운 액터와 히트되었을때
	{
		NewHitActor = InHitActor;
		TArray<USceneComponent*> ceilingSockets;

		GetBuildTransform(NewHitActor, ceilingSockets);

		if (ceilingSockets.Num() < 1) // ceilingSockets배열이 null일때
		{
			FRotator rotation = FRotator(BuildingObject->GetActorRotation().Pitch, OwnerPlayerController->PlayerCameraManager->K2_GetActorRotation().Yaw, BuildingObject->GetActorRotation().Roll);
			SpawnTransform = UKismetMathLibrary::MakeTransform(InHitLocation, rotation, FVector(1.f, 1.f, 1.05f));
			return;
		}
		else
		{
			SocketTransform.Empty();

			for (int i = 0; i < ceilingSockets.Num(); i++)
			{
				SocketTransform.Add(ceilingSockets[i]->GetComponentTransform());
			}
		}
	}

	if (SocketTransform.Num() < 1) // SocketTransform배열이 null일때
	{
		FRotator rotation = FRotator(BuildingObject->GetActorRotation().Pitch, OwnerPlayerController->PlayerCameraManager->K2_GetActorRotation().Yaw, BuildingObject->GetActorRotation().Roll);
		SpawnTransform = UKismetMathLibrary::MakeTransform(InHitLocation, rotation, FVector(1.f, 1.f, 1.05f));
		return;
	}

	float distance = 1e+5f;
	int index = 0;

	for (int i = 0; i < SocketTransform.Num(); i++)
	{
		float newDistance = UKismetMathLibrary::Vector_Distance(SocketTransform[i].GetLocation(), InHitLocation);
		if (newDistance < distance)
		{
			distance = newDistance;
			index = i;
		}
	}

	// 해당 Socket의 Location 및 Rotation 값 적용
	SpawnTransform = UKismetMathLibrary::MakeTransform(SocketTransform[index].GetLocation(), SocketTransform[index].GetRotation().Rotator(), FVector(1.f, 1.f, 1.05f));
}

void UBuildingComponent::Spawn()
{
	if (!!BuildingObject)
	{
		if (BuildingObject->IsCanBuild() && bInRange)
		{
			FTransform transform;
			transform = UKismetMathLibrary::MakeTransform(SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), FVector(1.f, 1.f, 1.f));

			GetWorld()->SpawnActor<ABaseBuildingObject>(BuildingObject->GetClass(), transform);
		}
		else
			CLog::Print("Can not Spawn");
	}
}

void UBuildingComponent::GetBuildTransform(ABaseBuildingObject* InHitActor, TArray<USceneComponent*>& OutComps)
{
	switch (InHitActor->BuildType)
	{
		case EBuildType::Ceiling:
		{
			ABuildingCeiling* actor = Cast<ABuildingCeiling>(NewHitActor);

			if (BuildingObject->BuildType == EBuildType::Ceiling)
			{
				if (!!actor->CeilingSockets)
					actor->CeilingSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::CeilingTriangle)
			{
				if (!!actor->CeilingTriangleSockets)
					actor->CeilingTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Roof) // roofsocket 하나라서 나중에 수정필요함
			{
				if (!!actor->RoofSocket)
					actor->RoofSocket->GetChildrenComponents(false, OutComps);
				break;
			}
			else
				break;
			
		}
		case EBuildType::CeilingTriangle:
		{
			ABuildingCeilingTriangle* actor = Cast<ABuildingCeilingTriangle>(NewHitActor);

			if (BuildingObject->BuildType == EBuildType::Ceiling)
			{
				if (!!actor->CeilingSockets)
					actor->CeilingSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::CeilingTriangle)
			{
				if (!!actor->CeilingTriangleSockets)
					actor->CeilingTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else
				break;
		}
		case EBuildType::Foundation:
		{
			ABuildingFoundation* actor = Cast<ABuildingFoundation>(NewHitActor);

			if (BuildingObject->BuildType == EBuildType::Foundation)
			{
				if (!!actor->FoundationSockets)
					actor->FoundationSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::FoundationTriangle)
			{
				if (!!actor->FoundationTriangleSockets)
					actor->FoundationTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Ramp)
			{
				if (!!actor->RampSockets)
					actor->RampSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else
				break;
		}
		case EBuildType::FoundationTriangle:
		{
			ABuildingFoundationTriangle* actor = Cast<ABuildingFoundationTriangle>(NewHitActor);

			if (BuildingObject->BuildType == EBuildType::Foundation)
			{
				if (!!actor->FoundationSockets)
					actor->FoundationSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::FoundationTriangle)
			{
				if (!!actor->FoundationTriangleSockets)
					actor->FoundationTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Ramp)
			{
				if (!!actor->RampSockets)
					actor->RampSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else
				break;
		}
		case EBuildType::Roof:
		{
			ABuildingRoof* actor = Cast<ABuildingRoof>(NewHitActor);

			if (BuildingObject->BuildType == EBuildType::Roof)
			{
				if (!!actor->RoofSockets)
					actor->RoofSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::RoofWall)
			{
				if (!!actor->RoofWallSockets)
					actor->RoofWallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Ceiling)
			{
				if (!!actor->CeilingSockets)
					actor->CeilingSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else
				break;
		}
		case EBuildType::Wall:
		{
			ABuildingWall* actor = Cast<ABuildingWall>(NewHitActor);

			if (BuildingObject->BuildType == EBuildType::Ceiling)
			{
				if (!!actor->CeilingSockets)
					actor->CeilingSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::CeilingTriangle)
			{
				if (!!actor->CeilingTriangleSockets)
					actor->CeilingTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildingObject->BuildType == EBuildType::Roof)
			{
				if (!!actor->RoofSockets)
					actor->RoofSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else
				break;

		}
		default:
			break;
	}

}

void UBuildingComponent::TrytoCreateBuildingWidget()
{
	if (!!BuildingWidgetClass)
	{
		TArray<class UUserWidget*> foundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), foundWidgets, BuildingWidgetClass);

		for (int i = 0; i < foundWidgets.Num(); i++)
		{
			BuildingWidget = foundWidgets[i];
		}
		
		BuildingWidget = CreateWidget(OwnerPlayerController, BuildingWidgetClass);
		BuildingWidget->AddToViewport();

	}
}

void UBuildingComponent::ShowBuildingMenu(bool Success)
{
	CheckNull(BuildingWidget)
	UHUDWidget* hudWidget = Cast<UHUDWidget>(BuildingWidget);

	CheckNull(hudWidget)
	hudWidget->ShowBuildingMenu_Interface();
}

void UBuildingComponent::HideBuildingMenu(bool Success)
{
	CheckNull(BuildingWidget)
		UHUDWidget* hudWidget = Cast<UHUDWidget>(BuildingWidget);

	CheckNull(hudWidget)
		hudWidget->HideBuildingMenu_Interface();
}

void UBuildingComponent::TryStartBuildObject(FDataTableRowHandle InBuildingObjectHandle)
{
	//CheckBuildRequirements(InBuildingObjectHandle); -> 자원추가할때 쓰는 함수
	StartBuildObject(InBuildingObjectHandle);
}

bool UBuildingComponent::CheckBuildRequirements(FDataTableRowHandle InBuildingObjectHandle)
{
	TSubclassOf<UIPlayer> iPlayerClass;
	if (UKismetSystemLibrary::DoesImplementInterface(OwnerPlayerController, iPlayerClass))
	{
		if (!!InBuildingObjectHandle.DataTable)
		{
			if (!!InBuildingObjectHandle.DataTable->FindRow<FBuildingObjectSettings>(InBuildingObjectHandle.RowName, ""))
				return true;
			else
				return false;
		}
	}
	return true;
}

void UBuildingComponent::StartBuildObject(FDataTableRowHandle InBuildingObjectHandle)
{
	CLog::Print("UBuildingComponent->StartBuildObject()");

	bool result;

	if (!!InBuildingObjectHandle.DataTable)
		result = InBuildingObjectHandle.RowName != FName("None");
	else
		result = false;

	if (result == true)
	{
		FBuildingObjectSettings* buildingObjectHandle = InBuildingObjectHandle.DataTable->FindRow<FBuildingObjectSettings>(InBuildingObjectHandle.RowName, "");
		if (!!buildingObjectHandle)
		{
			//ChangeBuildingMode(Enum);

			LastBuildingObjectHandle = buildingObjectHandle->Handle;
			LastBuildingObjectClass = buildingObjectHandle->Class;

			DestroyBuildingObject();

			FTransform transform;
			BuildingObject = GetWorld()->SpawnActor<ABaseBuildingObject>(LastBuildingObjectClass, transform);
			BuildingObject->BuildingObjectHandle = LastBuildingObjectHandle;
			BuildingObject->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			BuildingObject->SetMaterialCanBuild();
			BuildingObject->TryBuildMode();

			BuildTransform.SetLocation(FVector(0.f, 0.f, 0.f));
			BuildTransform.SetRotation(FQuat(FRotator(0.f, 0.f, 0.f)));
			BuildTransform.SetScale3D(FVector(1.f, 1.f, 1.f));
		}
	}
}

void UBuildingComponent::DestroyBuildingObject()
{
	if (!!BuildingObject)
	{
		BuildingObject->Destroy();
		BuildingObject = nullptr;
	}
}

