#include "CraftRPGPlayerController.h"
#include "Global.h"
#include "InputCoreTypes.h"
#include "Characters/PlayerCharacter.h"
#include "Components/BuildingComponent.h"

ACraftRPGPlayerController::ACraftRPGPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent(this, &BuildingComponent, "BuildingComponent");
}

void ACraftRPGPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraftRPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::E, IE_Pressed, this, &ACraftRPGPlayerController::FinishBuild);
	InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &ACraftRPGPlayerController::ShowBuildingMenu);
	InputComponent->BindKey(EKeys::Q, IE_Released, this, &ACraftRPGPlayerController::HideBuildingMenu);
	InputComponent->BindKey(EKeys::F10, IE_Released, this, &ACraftRPGPlayerController::StopBuildMode);
}

void ACraftRPGPlayerController::TryBuild(FDataTableRowHandle InBuildingObjectHandle)
{
	if(!!BuildingComponent)
		BuildingComponent->TryStartBuildObject(InBuildingObjectHandle);
}

void ACraftRPGPlayerController::FinishBuild()
{
	if (!!BuildingComponent)
		BuildingComponent->FinishBuildObject();
}

void ACraftRPGPlayerController::ShowBuildingMenu()
{
	if (!!BuildingComponent)
		BuildingComponent->ShowBuildingMenu();
}

void ACraftRPGPlayerController::HideBuildingMenu()
{
	if (!!BuildingComponent)
		BuildingComponent->HideBuildingMenu();
}

void ACraftRPGPlayerController::StopBuildMode()
{
	if (!!BuildingComponent)
		BuildingComponent->DestroyBuildingObject();
}

void ACraftRPGPlayerController::TryStartBuildObject_Interface(FDataTableRowHandle InBuildingObjectHandle)
{
	TryBuild(InBuildingObjectHandle);
}