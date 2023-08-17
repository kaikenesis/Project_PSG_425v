#include "BuildingComponent.h"
#include "GameFramework/Character.h"
#include "Global.h"
#include "BuildingObject/Modular/BuildingCeiling.h"
#include "BuildingObject/Modular/BuildingCeilingTriangle.h"
#include "BuildingObject/Modular/BuildingFoundation.h"
#include "BuildingObject/Modular/BuildingFoundationTriangle.h"
#include "BuildingObject/Modular/BuildingRoof.h"
#include "BuildingObject/Modular/BuildingWall.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CHelpers::GetClass(&BuildMeshClass, "Class'/Script/Project_PSG_425.BuildingCeiling'");
}


void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerPlayerController = Cast<APlayerController>(OwnerCharacter->GetController());
}


void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!!BuildMesh)
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

			FRotator rotation = FRotator(BuildMesh->GetActorRotation().Pitch ,OwnerPlayerController->PlayerCameraManager->K2_GetActorRotation().Yaw, BuildMesh->GetActorRotation().Roll);
			SpawnTransform = UKismetMathLibrary::MakeTransform(hitResult.Location, rotation, FVector(1.f, 1.f, 1.05f));
		}
		
		bInRange = hitResult.bBlockingHit;
		if(bInRange)
			BuildMesh->SetActorTransform(SpawnTransform);
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
	ignoreActor.Add(BuildMesh);
	ignoreActor.Add(OwnerCharacter);
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
			FRotator rotation = FRotator(BuildMesh->GetActorRotation().Pitch, OwnerPlayerController->PlayerCameraManager->K2_GetActorRotation().Yaw, BuildMesh->GetActorRotation().Roll);
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
			FRotator rotation = FRotator(BuildMesh->GetActorRotation().Pitch, OwnerPlayerController->PlayerCameraManager->K2_GetActorRotation().Yaw, BuildMesh->GetActorRotation().Roll);
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
		FRotator rotation = FRotator(BuildMesh->GetActorRotation().Pitch, OwnerPlayerController->PlayerCameraManager->K2_GetActorRotation().Yaw, BuildMesh->GetActorRotation().Roll);
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

void UBuildingComponent::CheckSpawn()
{
	OwnerPlayerController->bShowMouseCursor = true;

	if (!!BuildMeshClass && !BuildMesh)
	{
		FTransform transform;

		BuildMesh = GetWorld()->SpawnActor<ABaseBuildingObject>(BuildMeshClass, transform);
		BuildMesh->Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BuildMesh->SetMaterialCanBuild();

		BuildMesh->IsBuilded = false;
	}
}

void UBuildingComponent::Spawn()
{
	if (!!BuildMesh && BuildMesh->bCanBuild && bInRange)
	{
		FTransform transform;
		transform = UKismetMathLibrary::MakeTransform(SpawnTransform.GetLocation(), SpawnTransform.GetRotation().Rotator(), FVector(1.f, 1.f, 1.f));

		GetWorld()->SpawnActor<ABaseBuildingObject>(BuildMesh->GetClass(), transform);
	}
	else
		CLog::Print("Can not Spawn");
}

void UBuildingComponent::GetBuildTransform(ABaseBuildingObject* InHitActor, TArray<USceneComponent*>& OutComps)
{
	switch (InHitActor->BuildType)
	{
		case EBuildType::Ceiling:
		{
			ABuildingCeiling* actor = Cast<ABuildingCeiling>(NewHitActor);

			if (BuildMesh->BuildType == EBuildType::Ceiling)
			{
				if (!!actor->CeilingSockets)
					actor->CeilingSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::CeilingTriangle)
			{
				if (!!actor->CeilingTriangleSockets)
					actor->CeilingTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Roof) // roofsocket 하나라서 나중에 수정필요함
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

			if (BuildMesh->BuildType == EBuildType::Ceiling)
			{
				if (!!actor->CeilingSockets)
					actor->CeilingSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::CeilingTriangle)
			{
				if (!!actor->CeilingTriangleSockets)
					actor->CeilingTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Wall)
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

			if (BuildMesh->BuildType == EBuildType::Foundation)
			{
				if (!!actor->FoundationSockets)
					actor->FoundationSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::FoundationTriangle)
			{
				if (!!actor->FoundationTriangleSockets)
					actor->FoundationTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Ramp)
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

			if (BuildMesh->BuildType == EBuildType::Foundation)
			{
				if (!!actor->FoundationSockets)
					actor->FoundationSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::FoundationTriangle)
			{
				if (!!actor->FoundationTriangleSockets)
					actor->FoundationTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Ramp)
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

			if (BuildMesh->BuildType == EBuildType::Roof)
			{
				if (!!actor->RoofSockets)
					actor->RoofSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::RoofWall)
			{
				if (!!actor->RoofWallSockets)
					actor->RoofWallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Ceiling)
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

			if (BuildMesh->BuildType == EBuildType::Ceiling)
			{
				if (!!actor->CeilingSockets)
					actor->CeilingSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::CeilingTriangle)
			{
				if (!!actor->CeilingTriangleSockets)
					actor->CeilingTriangleSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Wall)
			{
				if (!!actor->WallSockets)
					actor->WallSockets->GetChildrenComponents(false, OutComps);
				break;
			}
			else if (BuildMesh->BuildType == EBuildType::Roof)
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

