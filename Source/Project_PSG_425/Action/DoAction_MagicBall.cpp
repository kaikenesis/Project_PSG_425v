#include "DoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"
#include "MagicBall.h"
#include "Aim.h"

void ADoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UAim>();
	Aim->BeginPlay(OwnerCharacter);

	ActionComp = CHelpers::GetComponent<UActionComponent>(OwnerCharacter);
	ActionComp->OnActionTypeChanged.AddDynamic(this, &ADoAction_MagicBall::AbortByTypeChanged);
}

void ADoAction_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ADoAction_MagicBall::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);

	if (Aim->IsAvailable())
		CheckFalse(Aim->IsZooming());

	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
}

void ADoAction_MagicBall::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckNull(Datas[0].ProjectileClass);

	FVector location;
	FRotator rotation;
	OwnerCharacter->GetController()->GetPlayerViewPoint(location, rotation);

	FVector handSocketLocation = OwnerCharacter->GetMesh()->GetSocketLocation("hand_r");
	FVector cameraDirection = rotation.Vector();
	location += cameraDirection * ((handSocketLocation - location) | cameraDirection);

	FTransform transform = Datas[0].EffectTransform;
	transform.AddToTranslation(location);
	transform.SetRotation(FQuat(OwnerCharacter->GetControlRotation()));

	AMagicBall* magicBall = GetWorld()->SpawnActorDeferred<AMagicBall>
		(
			Datas[0].ProjectileClass,
			transform,
			OwnerCharacter,
			OwnerCharacter,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

	magicBall->OnBeginOverlap.AddDynamic(this, &ADoAction_MagicBall::OnMagicBallBeginOverlap);

	magicBall->FinishSpawning(transform);
}

void ADoAction_MagicBall::End_DoAction()
{
	Super::End_DoAction();

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ADoAction_MagicBall::OnAim()
{
	Super::OnAim();

	Aim->On();
}

void ADoAction_MagicBall::OffAim()
{
	Super::OffAim();

	Aim->Off();
}

void ADoAction_MagicBall::OnMagicBallBeginOverlap(FHitResult InHitResult)
{
	FDamageEvent damageEvent;
	InHitResult.Actor->TakeDamage(Datas[0].Power, damageEvent, OwnerCharacter->GetController(), this);
}

void ADoAction_MagicBall::AbortByTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->IsAvailable());
	CheckFalse(Aim->IsZooming());
	Aim->Off();
}
