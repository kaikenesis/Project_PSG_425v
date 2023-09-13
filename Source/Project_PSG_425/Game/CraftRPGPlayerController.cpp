#include "CraftRPGPlayerController.h"
#include "Global.h"
#include "InputCoreTypes.h"
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

	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ACraftRPGPlayerController::FinishBuild);
	InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &ACraftRPGPlayerController::ShowBuildingMenu);
	InputComponent->BindKey(EKeys::Q, IE_Released, this, &ACraftRPGPlayerController::HideBuildingMenu);
}

void ACraftRPGPlayerController::TryBuild()
{
	if(!!BuildingComponent)
		BuildingComponent->CheckSpawn();
}

void ACraftRPGPlayerController::FinishBuild()
{
	if (!!BuildingComponent)
		BuildingComponent->Spawn();
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
