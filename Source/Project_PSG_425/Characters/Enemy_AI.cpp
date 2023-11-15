#include "Enemy_AI.h"
#include "Global.h"
#include "Components/PatrolComponent.h"

AEnemy_AI::AEnemy_AI()
{
	CHelpers::CreateActorComponent(this, &Patrol, "Patrol");
}
