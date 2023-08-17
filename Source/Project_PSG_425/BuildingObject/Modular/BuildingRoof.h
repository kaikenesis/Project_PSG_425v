#pragma once

#include "CoreMinimal.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "BuildingRoof.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuildingRoof : public ABaseBuildingObject
{
	GENERATED_BODY()
	
public:
	ABuildingRoof();

public:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* BuildComponents;

	//BuildCollision
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* BuildCollisions;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BuildCollision1;

	//Roof
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofSocket4;

	//RoofWall
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofWallSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofWallSocketLeft;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofWallSocketRight;

	//Ceiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket4;
};
