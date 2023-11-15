#include "BehaviorComponent.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/PlayerCharacter.h"

UBehaviorComponent::UBehaviorComponent()
{

}

void UBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UBehaviorComponent::IsWaitMode()
{
	return GetTypeFromBB() == EBehaviorType::Wait;
}

bool UBehaviorComponent::IsApproachMode()
{
	return GetTypeFromBB() == EBehaviorType::Approach;
}

bool UBehaviorComponent::IsAcionMode()
{
	return GetTypeFromBB() == EBehaviorType::Action;
}

bool UBehaviorComponent::IsPatrolMode()
{
	return GetTypeFromBB() == EBehaviorType::Patrol;
}

bool UBehaviorComponent::IsHittedMode()
{
	return GetTypeFromBB() == EBehaviorType::Hitted;
}

EBehaviorType UBehaviorComponent::GetTypeFromBB()
{
	return (EBehaviorType)Blackboard->GetValueAsEnum(BehaviorKey);
}

void UBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UBehaviorComponent::SetHittedMode()
{
	ChangeType(EBehaviorType::Hitted);
}

APlayerCharacter* UBehaviorComponent::GetPlayerKey()
{
	return Cast<APlayerCharacter>(Blackboard->GetValueAsObject(PlayerKey));
}

FVector UBehaviorComponent::GetLocationKey()
{
	return Blackboard->GetValueAsVector(LocationKey);
}

void UBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
	EBehaviorType prev = GetTypeFromBB();
	Blackboard->SetValueAsEnum(BehaviorKey, (uint8)InNewType);

	if (OnBehaviorTypeChanged.IsBound())
		OnBehaviorTypeChanged.Broadcast(prev, InNewType);
}

