#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "BuildingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PSG_425_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void BuildTraceResult(FHitResult& OutHitResult);
	void CheckDistance(FVector InHitLocation, class ABaseBuildingObject* InHitActor);

	void GetBuildTransform(class ABaseBuildingObject* InHitActor, TArray<class USceneComponent*>& OutComps);

	void TrytoCreateBuildingWidget();

	void ShowBuildingMenu(bool Success = false);
	void HideBuildingMenu(bool Success = false);

	void TryStartBuildObject(FDataTableRowHandle InBuildingObjectHandle);
	bool CheckBuildRequirements(FDataTableRowHandle InBuildingObjectHandle);
	void StartBuildObject(FDataTableRowHandle InBuildingObjectHandle);
	void FinishBuildObject();

	void DestroyBuildingObject();

public:
	FORCEINLINE bool IsBuildMode() { return bBuildMode; }

public:
	bool bTraceToMouseMode = false;
	float TraceDistance = 1000.f;

private:
	class APlayerController* OwnerPlayerController;

	bool bBuildMode;

	class ABaseBuildingObject* BuildingObject;
	class ABaseBuildingObject* NewHitActor;

	TArray<FTransform> SocketTransform;
	FTransform SpawnTransform;
	FRotator BuildingObjectRotation;

	TArray<class AActor*> OverlapActors;

	TSubclassOf<class UUserWidget> BuildingWidgetClass;
	class UUserWidget* BuildingWidget;

	TSubclassOf<class ABaseBuildingObject> LastBuildingObjectClass;
	FDataTableRowHandle LastBuildingObjectHandle;
	FTransform BuildTransform;
};
