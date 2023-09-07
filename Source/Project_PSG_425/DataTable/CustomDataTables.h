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
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FDataTableRowHandle Handle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FDataTableRowHandle> BuildingObjects;
};

USTRUCT(BlueprintType)
struct FBuildingObjectSettings : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FDataTableRowHandle Handle;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ABaseBuildingObject> Class;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FName Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UStaticMesh* StaticMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float MaxBurability;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bCanBeDamaged = true;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool bUseMeshSockets = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FTransform CorrectMeshTransform;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FDataTableRowHandle BuildingRequirements;
};

UCLASS()
class PROJECT_PSG_425_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
	
};
