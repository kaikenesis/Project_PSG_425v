#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "BaseBuildingObject.generated.h"

enum EBuildType
{
	Ceiling,
	CeilingTriangle,
	Foundation,
	FoundationTriangle,
	Roof,
	RoofWall,
	Wall,
	Ramp
};

enum EMeshType
{
	Wood,
	Stone,
	Metal
};

UCLASS()
class PROJECT_PSG_425_API ABaseBuildingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseBuildingObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnBeginOverlap(AActor* OverlapActor, AActor* OtherActor);

	UFUNCTION()
		virtual void OnEndOverlap(AActor* OverlapActor, AActor* OtherActor);

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() { return Mesh; }
	FORCEINLINE void TryBuildMode() { IsBuilded = false; }
	FORCEINLINE void FinishBuildMode() { IsBuilded = true; }
	FORCEINLINE bool IsCanBuild() { return bCanBuild; }
	
	void SetMaterialCanBuild();
	void SetMaterialCanNotBuild();

	void SetBuildType(EBuildType Type);
	virtual void SetMeshType(EMeshType Type);

public:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Mesh;

private:
	class UMaterialInterface* CanBuildMaterialInterface;
	class UMaterialInterface* CanNotBuildMaterialInterface;

	bool IsBuilded = true;
	bool bCanBuild = true;

public:
	EBuildType BuildType;
	EMeshType MeshType;

	TArray<AActor*> OverlapActors;

	FDataTableRowHandle BuildingObjectHandle;

protected:
	UStaticMesh* MeshWood;
	UStaticMesh* MeshStone;
	UStaticMesh* MeshMetal;
};
