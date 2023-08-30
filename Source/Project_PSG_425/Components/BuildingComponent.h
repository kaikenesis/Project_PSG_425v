#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingObject/BaseBuildingObject.h"
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
	void CheckDistance(FVector InHitLocation, ABaseBuildingObject* InHitActor);
	void CheckSpawn();
	void Spawn();

	void GetBuildTransform(ABaseBuildingObject* InHitActor, TArray<USceneComponent*>& OutComps);

	void TrytoCreateBuildingWidget();

	void ShowBuildingMenu(bool Success = false);
	void HideBuildingMenu(bool Success = false);

private:
	class APlayerController* OwnerPlayerController;

	class ABaseBuildingObject* BuildMesh;
	class ABaseBuildingObject* NewHitActor;
	TSubclassOf<class ABaseBuildingObject> BuildMeshClass;

	TArray<FTransform> SocketTransform;
	FTransform SpawnTransform;

	TArray<AActor*> OverlapActors;

	TSubclassOf<class UUserWidget> BuildingWidgetClass;
	class UUserWidget* BuildingWidget;

	bool bInRange = false;
};
