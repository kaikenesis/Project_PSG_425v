#pragma once

#include "CoreMinimal.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "BuildingFoundationTriangle.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuildingFoundationTriangle : public ABaseBuildingObject
{
	GENERATED_BODY()
	
public:
	ABuildingFoundationTriangle();

public:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* BuildComponents;

	//BuildCollision
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* BuildCollisions;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BuildCollision1;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BuildCollision2;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BuildCollision3;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BuildCollision4;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BuildCollision5;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BuildCollision6;

	//Ceiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket3;

	//TriangleCeiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket3;

	//Wall
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket3;

	//Ramp
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket3;
};
