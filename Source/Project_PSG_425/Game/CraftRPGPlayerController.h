#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CraftRPGPlayerController.generated.h"

UCLASS()
class PROJECT_PSG_425_API ACraftRPGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ACraftRPGPlayerController();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

private:
	void CheckBuild();
	void SpawnBuild();
	void ShowBuildingMenu();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UBuildingComponent* BuildingComponent;

private:
	FTransform SpawnTransform;
};