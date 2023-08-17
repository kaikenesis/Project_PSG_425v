#pragma once

#include "CoreMinimal.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "BuildingWall.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuildingWall : public ABaseBuildingObject
{
	GENERATED_BODY()
	
public:
	ABuildingWall();

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
		class USceneComponent* CeilingSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket4;

	//CeilingTriangle
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSockets;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSocket4;

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

};
