#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemy.h"
#include "Enemy_AI.generated.h"

UCLASS()
class PROJECT_PSG_425_API AEnemy_AI : public AEnemy
{
	GENERATED_BODY()
	
public:
	AEnemy_AI();

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UPatrolComponent* Patrol;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
		uint8 TeamID = 1;
};
