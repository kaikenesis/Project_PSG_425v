#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PSG_425_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPatrolComponent();

protected:
	virtual void BeginPlay() override;

public:	
	FORCEINLINE bool IsPathValid() { return Path != nullptr; }

	bool GetMoveToLocation(FVector& OutLocation);
	void UpdateNextIndex();

private:
	UPROPERTY(EditInstanceOnly)
		class APatrolPath* Path;

	UPROPERTY(EditAnywhere)
		bool bReverse;

	UPROPERTY(EditAnywhere)
		int32 Index;
};
