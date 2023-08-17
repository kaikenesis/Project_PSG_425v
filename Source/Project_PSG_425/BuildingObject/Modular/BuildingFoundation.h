#pragma once

#include "CoreMinimal.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "BuildingFoundation.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuildingFoundation : public ABaseBuildingObject
{
	GENERATED_BODY()
	
public:
	ABuildingFoundation();

public:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* BuildComponents;

	//BuildCollision
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* BuildCollisions;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* BuildCollision1;

	//Ceiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket4;

	//TriangleCeiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket4;

	//Wall
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket4;

	//Ramp
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket4;

	//Stairs, Roof
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* StairsSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofSocket;
};
