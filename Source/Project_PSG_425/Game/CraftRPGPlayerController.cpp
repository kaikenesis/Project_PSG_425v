#include "CraftRPGPlayerController.h"
#include "Global.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "BuildingObject/Modular/BuildingCeiling.h"
#include "InputCoreTypes.h"
#include "Camera/PlayerCameraManager.h"

ACraftRPGPlayerController::ACraftRPGPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::GetClass(&Ceiling, "Class'/Script/Project_PSG_425.BuildingCeiling'");
}

void ACraftRPGPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!!BaseBuildObject)
	{
		float mouseX, mouseY;
		FVector start, worldDirection;
		GetMousePosition(mouseX, mouseY);
		DeprojectScreenPositionToWorld(mouseX, mouseY, start, worldDirection);
		FVector end = start + (worldDirection * 1000.f);

		TArray<AActor*> actors;
		actors.Add(BaseBuildObject);
		actors.Add(PlayerCameraManager);
		actors.Add(this);

		FHitResult hitResult;

		UKismetSystemLibrary::LineTraceSingle
		(
			this,
			start,
			end,
			ETraceTypeQuery::TraceTypeQuery1,
			false,
			actors,
			EDrawDebugTrace::ForDuration,
			hitResult,
			true
		);

		ABaseBuildingObject* buildObject = Cast<ABaseBuildingObject>(hitResult.Actor);
		if (!!buildObject)
		{
			switch (buildObject->BuildType)
			{
			case EBuildType::Ceiling:
			{
				//ABuildingCeiling* ceiling = Cast<ABuildingCeiling>(hitResult.Actor);
				//ceiling->CeilingSocket1->GetComponentTransform();
				//SpawnTransform;
			}
			case EBuildType::CeilingTriangle:
			case EBuildType::Foundation:
			case EBuildType::FoundationTriangle:
			case EBuildType::Roof:
			case EBuildType::Wall:

			default:
				break;
			}
		}

		SpawnTransform.SetLocation(hitResult.Location);
		SpawnTransform.SetRotation(FQuat(FRotator(0.f, PlayerCameraManager->GetCameraRotation().Yaw, 0.f)));

		BaseBuildObject->SetActorTransform(SpawnTransform);
	}

}

void ACraftRPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::One, IE_Pressed, this, &ACraftRPGPlayerController::CheckBuild);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ACraftRPGPlayerController::SpawnBuild);
}

void ACraftRPGPlayerController::CheckBuild()
{
	bShowMouseCursor = true;

	if (!!Ceiling)
	{
		FTransform transform;

		BaseBuildObject = GetWorld()->SpawnActor<ABaseBuildingObject>(Ceiling, transform);
		BaseBuildObject->SetActorEnableCollision(false);
		BaseBuildObject->SetMaterialCanBuild();
	}	
}

void ACraftRPGPlayerController::SpawnBuild()
{
	GetWorld()->SpawnActor<ABaseBuildingObject>(Ceiling, SpawnTransform);
}
