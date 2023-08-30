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

	InputComponent->BindKey(EKeys::One, IE_Pressed, this, &ACraftRPGPlayerController::CheckBuild);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &ACraftRPGPlayerController::SpawnBuild);
	//InputComponent->BindKey(EKeys::Q, IE_Pressed, this, &UBuildingComponent::ShowBuildingMenu);
}

void ACraftRPGPlayerController::CheckBuild()
{
	if(!!BuildingComponent)
		BuildingComponent->CheckSpawn();
}

void ACraftRPGPlayerController::SpawnBuild()
{
	if (!!BuildingComponent)
		BuildingComponent->Spawn();
}
