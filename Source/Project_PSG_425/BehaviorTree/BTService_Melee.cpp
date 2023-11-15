#include "BTService_Melee.h"
#include "Global.h"
#include "Components/BehaviorComponent.h"
#include "Components/StateComponent.h"
#include "Components/PatrolComponent.h"
#include "Characters/Enemy_AI.h"
#include "Characters/PlayerCharacter.h"
#include "Game/AIController_Enemy.h"

UBTService_Melee::UBTService_Melee()
{
	NodeName = "Melee";
}

void UBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController_Enemy* controller = Cast<AAIController_Enemy>(OwnerComp.GetOwner());
	CheckNull(controller);

	UBehaviorComponent* behaviorComp = CHelpers::GetComponent<UBehaviorComponent>(controller);
	CheckNull(behaviorComp);

	AEnemy_AI* enemy = Cast<AEnemy_AI>(controller->GetPawn());
	CheckNull(enemy);

	UStateComponent* stateComp = CHelpers::GetComponent<UStateComponent>(enemy);
	CheckNull(stateComp);

	UPatrolComponent* patrolComp = CHelpers::GetComponent<UPatrolComponent>(enemy);
	CheckNull(patrolComp);

	//Hitted
	if (stateComp->IsHittedMode())
	{
		behaviorComp->SetHittedMode();
		return;
	}

	//Get Player from BB
	APlayerCharacter* player = behaviorComp->GetPlayerKey();

	//No Perceived Player
	if (player == nullptr)
	{
		if (patrolComp->IsPathValid())
		{
			behaviorComp->SetPatrolMode();
			return;
		}

		behaviorComp->SetWaitMode();
		return;
	}

	//Perceived Player
	UStateComponent* playerStateComp = CHelpers::GetComponent<UStateComponent>(player);
	if (!!playerStateComp)
	{
		if (playerStateComp->IsDeadMode())
		{
			behaviorComp->SetWaitMode();
			return;
		}
	}

	//Get Distance to Player
	float distance = enemy->GetDistanceTo(player);

	//Is in Attack Range
	if (distance < controller->GetBehaviorRange())
	{
		behaviorComp->SetActionMode();
		return;
	}

	//Is in Sight Range
	if (distance < controller->GetSightRadius())
	{
		behaviorComp->SetApproachMode();
		return;
	}

}
