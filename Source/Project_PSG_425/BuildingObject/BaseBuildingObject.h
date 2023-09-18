#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTable/CustomDataTables.h"
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
		virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() { return Mesh; }
	FORCEINLINE void TryBuildMode() { IsBuilded = false; }
	FORCEINLINE void FinishBuildMode() { IsBuilded = true; }
	FORCEINLINE bool IsCanBuild() { return bCanBuild; }
	FORCEINLINE bool IsOverlappedObject() { return OverlapActors.Num() > 0; }
	
	void SetCanBuild();
	void SetCanNotBuild();

private:
	void SetCanBeBuilt(bool InCanBeBuilt);
	void InitOverlapSettings();

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

	TArray<class AActor*> OverlapActors;

public:
	EBuildType BuildType;
	EMeshType MeshType;

	FDataTableRowHandle BuildingObjectHandle;

private:
	FBuildingObjectSettings* BuildingObjectSettings;

};
