#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuildingObject.generated.h"

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

protected:
	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* Mesh;

};
