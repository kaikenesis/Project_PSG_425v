#include "StateComponent.h"

UStateComponent::UStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStateComponent::SetIdleMode()
{
	ChangeType(EStateType::Idle);
}

void UStateComponent::SetRollMode()
{
	ChangeType(EStateType::Roll);
}

void UStateComponent::SetEvadeMode()
{
	ChangeType(EStateType::Evade);
}

void UStateComponent::SetEquipMode()
{
	ChangeType(EStateType::Equip);
}

void UStateComponent::SetActionMode()
{
	ChangeType(EStateType::Action);
}

void UStateComponent::SetBlockMode()
{
	ChangeType(EStateType::Block);
}

void UStateComponent::SetHittedMode()
{
	ChangeType(EStateType::Hitted);
}

void UStateComponent::SetDeadMode()
{
	ChangeType(EStateType::Dead);
}

void UStateComponent::ChangeType(EStateType InNewType)
{
	EStateType prev = Type;
	Type = InNewType;

	if (OnStateTypeChanged.IsBound())
		OnStateTypeChanged.Broadcast(prev, InNewType);
}

