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

private:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* BuildComponents;

	//Ceiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationSocket3;

	//TriangleCeiling
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* FoundationTriangleSocket3;

	//Wall
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* WallSocket3;

	//Ramp
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket1;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket2;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* RampSocket3;
};
