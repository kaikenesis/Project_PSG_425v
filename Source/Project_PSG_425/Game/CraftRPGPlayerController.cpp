#include "CraftRPGPlayerController.h"
#include "Global.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "BuildingObject/Modular/BuildingCeiling.h"
#include "InputCoreTypes.h"
#include "Camera/PlayerCameraManager.h"
#include "Characters/PlayerCharacter.h"

ACraftRPGPlayerController::ACraftRPGPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
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
}

void ACraftRPGPlayerController::CheckBuild()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if(!!player)
		player->CheckSpawn();
}

void ACraftRPGPlayerController::SpawnBuild()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!!player)
		player->Spawn();
}
