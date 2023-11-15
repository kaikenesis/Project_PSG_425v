#include "BTTaskNode_Action.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/Enemy.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"

UBTTaskNode_Action::UBTTaskNode_Action()
{
    NodeName = "Action";

    bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNullResult(controller, EBTNodeResult::Failed);

	AEnemy* enemy = Cast<AEnemy>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(enemy);
	CheckNullResult(actionComp, EBTNodeResult::Failed);

	actionComp->DoAction();

	RunningTime = 0.f;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNull(controller);

	AEnemy* enemy = Cast<AEnemy>(controller->GetPawn());
	CheckNull(enemy);

	UStateComponent* stateComp = CHelpers::GetComponent<UStateComponent>(enemy);
	CheckNull(stateComp);

	RunningTime += DeltaSeconds;

	if (stateComp->IsIdleMode() && RunningTime >= Delay)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
