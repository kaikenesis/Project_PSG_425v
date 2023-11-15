#include "BTTaskNode_MoveSpeed.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/Enemy.h"

UBTTaskNode_MoveSpeed::UBTTaskNode_MoveSpeed()
{
	NodeName = "MoveSpeed";
}

EBTNodeResult::Type UBTTaskNode_MoveSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNullResult(controller, EBTNodeResult::Failed);

	AEnemy* enemy = Cast<AEnemy>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	UStatusComponent* statusComp = CHelpers::GetComponent<UStatusComponent>(enemy);
	CheckNullResult(statusComp, EBTNodeResult::Failed);

	statusComp->ChangeMoveSpeed(Type);

	return EBTNodeResult::Succeeded;
}
