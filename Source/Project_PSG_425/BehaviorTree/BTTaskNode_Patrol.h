#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Patrol.generated.h"

UCLASS()
class PROJECT_PSG_425_API UBTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_Patrol();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 20.f;
};
