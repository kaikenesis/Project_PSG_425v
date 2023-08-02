#pragma once

#include "CoreMinimal.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "BuildingCeilingTriangle.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuildingCeilingTriangle : public ABaseBuildingObject
{
	GENERATED_BODY()
	
public:
	ABuildingCeilingTriangle();

private:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* BuildComponents;

	//Ceiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket3;

	//TriangleCeiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingTriangleSocket3;

	//Wall
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket4;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket5;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket6;

};
