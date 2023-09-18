#include "StatusComponent.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}


void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStatusComponent::SetMove()
{
	bCanMove = true;
}

void UStatusComponent::SetStop()
{
	bCanMove = false;
}

void UStatusComponent::IncreaseHealth(float InAmount)
{
	CurrentHealth -= InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UStatusComponent::DecreaseHealth(float InAmount)
{
	CurrentHealth += InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}