#pragma once

#include "CoreMinimal.h"
#include "BuildingObject/Modular/BuildingWall.h"
#include "BuildingDoorFrame.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuildingDoorFrame : public ABuildingWall
{
	GENERATED_BODY()
	
public:
	ABuildingDoorFrame();

private:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* DoorSocket;

};
