#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/IPlayer.h"
#include "CraftRPGPlayerController.generated.h"

UCLASS()
class PROJECT_PSG_425_API ACraftRPGPlayerController : public APlayerController, public IIPlayer
{
	GENERATED_BODY()
	
public:
	ACraftRPGPlayerController();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

public:
	virtual void TryStartBuildObject_Interface(FDataTableRowHandle InBuildingObjectHandle) override;

private:
	void TryBuild(FDataTableRowHandle InBuildingObjectHandle);
	void FinishBuild();
	void ShowBuildingMenu();
	void HideBuildingMenu();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBuildingComponent* BuildingComponent;

private:
	FTransform SpawnTransform;
};