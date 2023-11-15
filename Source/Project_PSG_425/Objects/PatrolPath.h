#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class PROJECT_PSG_425_API APatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	APatrolPath();

	virtual void OnConstruction(const FTransform& Transform) override;
protected:
	virtual void BeginPlay() override;

public:	
	FORCEINLINE class USplineComponent* GetSpline() { return Spline; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class USplineComponent* Spline;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

private:
	UPROPERTY(EditInstanceOnly)
		bool bClosedLoop;
};
