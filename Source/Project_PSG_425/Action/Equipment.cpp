#include "Equipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

AEquipment::AEquipment()
{

}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	StateComp = CHelpers::GetComponent<UStateComponent>(OwnerCharacter);
	StatusComp = CHelpers::GetComponent<UStatusComponent>(OwnerCharacter);
}

void AEquipment::Equip_Implementation()
{
	StateComp->SetEquipMode();

	Data.bCanMove ? StatusComp->SetMove() : StatusComp->SetStop();

	//Play Montage
	if (!!Data.AnimMontage)
		OwnerCharacter->PlayAnimMontage(Data.AnimMontage, Data.PlayRate, Data.StartSection);
	else
	{
		Begin_Equip();
		End_Equip();
	}

	//bLookForward
	if (Data.bLookForward == true)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void AEquipment::Begin_Equip_Implementation()
{
	if (OnBeginEquip.IsBound())
		OnBeginEquip.Broadcast();
}

void AEquipment::End_Equip_Implementation()
{
	StateComp->SetIdleMode();
	StatusComp->SetMove();
}

void AEquipment::Unequip_Implementation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

	if (OnUnequip.IsBound())
		OnUnequip.Broadcast();
}

