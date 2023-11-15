#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/StatusComponent.h"
#include "BTTaskNode_MoveSpeed.generated.h"

UCLASS()
class PROJECT_PSG_425_API UBTTaskNode_MoveSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_MoveSpeed();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
		EWalkSpeedType Type;
};
