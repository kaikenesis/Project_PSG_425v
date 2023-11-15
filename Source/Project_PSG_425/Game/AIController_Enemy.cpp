#include "AIController_Enemy.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/BehaviorComponent.h"
#include "Characters/Enemy_AI.h"
#include "Characters/PlayerCharacter.h"

AAIController_Enemy::AAIController_Enemy()
{
    PrimaryActorTick.bCanEverTick = true;

    CHelpers::CreateActorComponent(this, &Blackboard, "Blackboard");
    CHelpers::CreateActorComponent(this, &Behavior, "Behavior");
    CHelpers::CreateActorComponent(this, &Perception, "Perception");

    Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
    Sight->SightRadius = 600.f;
    Sight->LoseSightRadius = 800.f;
    Sight->PeripheralVisionAngleDegrees = 80.f;
    Sight->SetMaxAge(2.f);
    Sight->DetectionByAffiliation.bDetectEnemies = true;
    Sight->DetectionByAffiliation.bDetectFriendlies = false;
    Sight->DetectionByAffiliation.bDetectNeutrals = false;

    Perception->ConfigureSense(*Sight);
    Perception->SetDominantSense(Sight->GetSenseImplementation());
}

void AAIController_Enemy::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    PossessedEnemy = Cast<AEnemy_AI>(InPawn);
    UseBlackboard(PossessedEnemy->GetBehaviorTree()->BlackboardAsset, Blackboard);

    Behavior->SetBlackboard(Blackboard);

    SetGenericTeamId(PossessedEnemy->GetTeamID());
    RunBehaviorTree(PossessedEnemy->GetBehaviorTree());

    Perception->OnPerceptionUpdated.AddDynamic(this, &AAIController_Enemy::OnPerceptionUpdated);
}

void AAIController_Enemy::OnUnPossess()
{
    Super::OnUnPossess();

    Perception->OnPerceptionUpdated.Clear();
}

void AAIController_Enemy::BeginPlay()
{
    Super::BeginPlay();
}

void AAIController_Enemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckFalse(bDrawDebug);

    FVector center = PossessedEnemy->GetActorLocation();

    DrawDebugSphere(GetWorld(), center, Sight->SightRadius, 30, FColor::Green);
    DrawDebugSphere(GetWorld(), center, BehaviorRange, 30, FColor::Red);
}

float AAIController_Enemy::GetSightRadius()
{
    return Sight->SightRadius;
}

void AAIController_Enemy::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
    TArray<AActor*> actors;
    Perception->GetCurrentlyPerceivedActors(nullptr, actors);

    APlayerCharacter* player = nullptr;
    for (const auto& actor : actors)
    {
        player = Cast<APlayerCharacter>(actor);
        if (!!player)
            break;
    }

    Blackboard->SetValueAsObject("PlayerKey", player);
}
