#include "DoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

void ADoAction_Melee::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);

	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;

		return;
	}

	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();

	//첫공격만 실행
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ADoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bSucceed);
	bSucceed = false;

	OwnerCharacter->StopAnimMontage();

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].AnimMontage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();
}

void ADoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->StopAnimMontage(Datas[ComboCount].AnimMontage);
	ComboCount = 0;

	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void ADoAction_Melee::OnBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	//Register HittedCharacters
	int32 hittedCharactersNum = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);

	CheckFalse(hittedCharactersNum < HittedCharacters.Num());

	//HitStop
	float hitStop = Datas[ComboCount].HitStop;
	if (FMath::IsNearlyZero(hitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.02f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreTimeDilation", 0.02f * hitStop, false);
	}

	TSubclassOf<UCameraShake> shakeClass = Datas[ComboCount].ShakeClass;
	if (!!shakeClass)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!!controller)
			controller->PlayerCameraManager->PlayCameraShake(shakeClass);
	}

	//Play Particle
	UParticleSystem* effect = Datas[ComboCount].Effect;
	if (!!effect)
	{
		FTransform transform = Datas[ComboCount].EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), effect, transform);
	}

	//TakeDamage
	FDamageEvent damageEvent;
	InOtherCharacter->TakeDamage(Datas[ComboCount].Power, damageEvent, InAttacker->GetController(), InCauser);
}

void ADoAction_Melee::OnEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

void ADoAction_Melee::RestoreTimeDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}
