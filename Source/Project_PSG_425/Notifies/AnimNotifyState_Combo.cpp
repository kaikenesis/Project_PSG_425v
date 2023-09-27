#include "AnimNotifyState_Combo.h"
#include "Global.h"
#include "Components/ActionComponent.h"
#include "Action/ActionData.h"
#include "Action/DoAction_Melee.h"

FString UAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	ADoAction_Melee* doAction_melee = Cast<ADoAction_Melee>(currentData->GetDoAction());
	CheckNull(doAction_melee);
	doAction_melee->EnableCombo();
}

void UAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	ADoAction_Melee* doAction_melee = Cast<ADoAction_Melee>(currentData->GetDoAction());
	CheckNull(doAction_melee);
	doAction_melee->DisableCombo();
}
