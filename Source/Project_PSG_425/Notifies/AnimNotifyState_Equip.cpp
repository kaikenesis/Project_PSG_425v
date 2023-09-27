#include "AnimNotifyState_Equip.h"
#include "Global.h"
#include "Components/ActionComponent.h"
#include "Action/ActionData.h"
#include "Action/Equipment.h"

FString UAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	AEquipment* equipment = currentData->GetEquipment();
	CheckNull(equipment);

	equipment->Begin_Equip();
}

void UAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	AEquipment* equipment = currentData->GetEquipment();
	CheckNull(equipment);

	equipment->End_Equip();
}
