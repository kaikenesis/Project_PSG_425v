#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_RandomMove.generated.h"

UCLASS()
class PROJECT_PSG_425_API UBTTaskNode_RandomMove : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_RandomMove();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
		float RandomPointRadius = 300.f;

	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 10.f;

private:
	FVector RandomLocation;
};
