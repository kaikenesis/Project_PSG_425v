#include "BTTaskNode_Patrol.h"
#include "Global.h"
#include "AIController.h"
#include "Components/PatrolComponent.h"
#include "Characters/Enemy_AI.h"

UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNullResult(controller, EBTNodeResult::Failed);

	AEnemy_AI* enemy = Cast<AEnemy_AI>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	UPatrolComponent* patrolComp = CHelpers::GetComponent<UPatrolComponent>(enemy);
	CheckNullResult(patrolComp, EBTNodeResult::Failed);

	if (patrolComp->IsPathValid() == false)
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNull(controller);

	AEnemy_AI* enemy = Cast<AEnemy_AI>(controller->GetPawn());
	CheckNull(enemy);

	UPatrolComponent* patrolComp = CHelpers::GetComponent<UPatrolComponent>(enemy);
	CheckNull(patrolComp);

	FVector location;
	patrolComp->GetMoveToLocation(location);

	EPathFollowingRequestResult::Type result = controller->MoveToLocation(location, AcceptanceRadius);
	if (result == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		patrolComp->UpdateNextIndex();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
