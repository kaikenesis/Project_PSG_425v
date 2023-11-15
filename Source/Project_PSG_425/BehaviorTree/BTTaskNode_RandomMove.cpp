#include "BTTaskNode_RandomMove.h"
#include "Global.h"
#include "AIController.h"
#include "Characters/Enemy_AI.h"
#include "NavigationSystem.h"

UBTTaskNode_RandomMove::UBTTaskNode_RandomMove()
{
	NodeName = "MoveToRandomLocation";
}

EBTNodeResult::Type UBTTaskNode_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();

	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNullResult(controller, EBTNodeResult::Failed);

	AEnemy_AI* enemy = Cast<AEnemy_AI>(controller->GetPawn());
	CheckNullResult(enemy, EBTNodeResult::Failed);

	FVector origin = enemy->GetActorLocation();
	//UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(GetWorld(), origin, RandomLocation, RandomPointRadius);
	RandomLocation = UNavigationSystemV1::GetRandomPointInNavigableRadius(GetWorld(), origin, RandomPointRadius);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_RandomMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* controller = OwnerComp.GetAIOwner();
	CheckNull(controller);

	controller->MoveToLocation(RandomLocation);

	EPathFollowingRequestResult::Type result = controller->MoveToLocation(RandomLocation, AcceptanceRadius);

	if (result == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	if (result == EPathFollowingRequestResult::RequestSuccessful)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
