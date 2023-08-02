#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuildingObject.generated.h"

enum EBuildType
{
	Ceiling,
	CeilingTriangle,
	Foundation,
	FoundationTriangle,
	Roof,
	Wall
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

public:
	void SetMaterialCanBuild();
	void SetMaterialCanNotBuild();

public:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Mesh;

private:
	class UMaterialInterface* CanBuildMaterialInterface;
	class UMaterialInterface* CanNotBuildMaterialInterface;

public:
	EBuildType BuildType;
};
