#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "BuildingObject/BaseBuildingObject.h"
#include "CustomDataTables.generated.h"

USTRUCT(BlueprintType)
struct FBuildingList : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FDataTableRowHandle Handle;

	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		FName Description;

	UPROPERTY(EditAnywhere)
		TArray<FDataTableRowHandle> BuildingObjects;
};

USTRUCT(BlueprintType)
struct FBuildingObjectSettings : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FDataTableRowHandle Handle;

	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABaseBuildingObject> Class;

	UPROPERTY(EditAnywhere)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
		FName Description;

	UPROPERTY(EditAnywhere)
		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere)
		float MaxBurability;

	UPROPERTY(EditAnywhere)
		bool bCanBeDamaged = true;

	UPROPERTY(EditAnywhere)
		bool bUseMeshSockets = false;

	UPROPERTY(EditAnywhere)
		FTransform CorrectMeshTransform;

	UPROPERTY(EditAnywhere)
		FDataTableRowHandle BuildingRequirements;
};

UCLASS()
class PROJECT_PSG_425_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
	
};
