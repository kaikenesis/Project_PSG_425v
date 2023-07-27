#pragma once

#include "CoreMinimal.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "BuildingCeiling.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuildingCeiling : public ABaseBuildingObject
{
	GENERATED_BODY()
	
public:
	ABuildingCeiling();

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

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* CeilingSocket4;

	//TriangleCeiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* TriangleCeilingSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* TriangleCeilingSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* TriangleCeilingSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* TriangleCeilingSocket3;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* TriangleCeilingSocket4;

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

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket7;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket8;

	//Stairs, Roof
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* StairsSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RoofSocket;
};
