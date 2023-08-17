#pragma once

#include "CoreMinimal.h"
#include "BuildingObject/Modular/BuildingWall.h"
#include "BuildingWindowFrame.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuildingWindowFrame : public ABuildingWall
{
	GENERATED_BODY()
	
public:
	ABuildingWindowFrame();

public:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WindowSocket;
};
