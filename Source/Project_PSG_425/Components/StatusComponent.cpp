#include "StatusComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StateComponent.h"
#include "Components/WidgetComponent.h"
#include "Action/BuffParticle.h"
#include "Widgets/HealthWidget.h"

UStatusComponent::UStatusComponent()
{
	
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	StateComp = CHelpers::GetComponent<UStateComponent>(OwnerCharacter);

	// Character안에 WidgetComponent를 가져와 그중에서 HealthWidget의 이름을 가진 Component탐색
	TSet<UActorComponent*> actorComps = OwnerCharacter->GetComponents();
	UWidgetComponent* healthWidgetComp = nullptr;

	for (const auto& actorComp : actorComps)
	{
		UWidgetComponent* widgetComp = Cast<UWidgetComponent>(actorComp);
		if (!!widgetComp)
		{
			if (widgetComp->GetName() == "HealthWidget")
				healthWidgetComp = Cast<UWidgetComponent>(actorComp);
		}
	}

	if (!!healthWidgetComp)
		HealthWidget = Cast<UHealthWidget>(healthWidgetComp->GetUserWidgetObject());

	CurrentHealth = MaxHealth;
}

void UStatusComponent::SetMove()
{
	bCanMove = true;
}

void UStatusComponent::SetStop()
{
	bCanMove = false;
}

void UStatusComponent::ChangeMoveSpeed(EWalkSpeedType InType)
{
	CheckNull(OwnerCharacter);

	UCharacterMovementComponent* movementComp = CHelpers::GetComponent<UCharacterMovementComponent>(OwnerCharacter);
	CheckNull(movementComp);

	movementComp->MaxWalkSpeed = WalkSpeed[(int32)InType];
}

void UStatusComponent::IncreaseHealth(float InAmount)
{
	CurrentHealth += InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UStatusComponent::DecreaseHealth(float InAmount)
{
	CurrentHealth -= InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UStatusComponent::PlayBurn(float InTickTime, int32 InTickCount, float TickDamage, FTransform InTransform, bool IsLoop, UParticleSystem* InParticle)
{
	if (BurnImmune == true)
		return;

	SetBurnCount(InTickCount);
	SetBurnTickDamage(TickDamage);
	PlayEffect(InParticle, InTransform, InTickTime * (float)InTickCount);
	UKismetSystemLibrary::K2_SetTimer(this, "Burn", InTickTime, IsLoop);
}

void UStatusComponent::Burn()
{
	if (BurnCount <= 0)
		UKismetSystemLibrary::K2_ClearTimer(this, "Burn");

	DecreaseHealth(BurnTickDamage);
	UpdateHealthWidget();
	BurnCount--;
}

void UStatusComponent::PlayEffect(UParticleSystem* InParticle, FTransform InTransform, float InTime)
{
	//Play Particle
	if (!!ParticleClass)
	{
		FTransform transform;
		ABuffParticle* particle = nullptr;
		particle = OwnerCharacter->GetWorld()->SpawnActorDeferred<ABuffParticle>(ParticleClass, transform, OwnerCharacter);
		particle->AttachToComponent
		(
			OwnerCharacter->GetMesh(),
			FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, EAttachmentRule::KeepRelative, true),
			"StatusAbnormality"
		);
		particle->Get()->SetTemplate(InParticle);
		UGameplayStatics::FinishSpawningActor(particle, transform);
		CLog::Log(particle);
		particle->Play(InTime);
	}
}

void UStatusComponent::UpdateHealthWidget()
{
	//Apply Health Widget
	if (!!HealthWidget)
		HealthWidget->UpdateHealth(GetCurrentHealth(), GetMaxHealth());

	if (IsDead() == true)
		StateComp->SetDeadMode();
}
