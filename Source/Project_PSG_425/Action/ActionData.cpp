#include "ActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Equipment.h"
#include "Attachment.h"
#include "DoAction.h"

void UActionData::BeginPlay(class ACharacter* InOwnerCharacter, UActionData_Spawned** OutSpawned)
{
	FTransform transform;

	AAttachment* attachment = nullptr;
	if (!!AttachmentClass)
	{
		attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<AAttachment>(AttachmentClass, transform, InOwnerCharacter);
		attachment->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "Attachment"));
		UGameplayStatics::FinishSpawningActor(attachment, transform);
	}

	AEquipment* equipment = nullptr;
	if (!!EquipmentClass)
	{
		equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<AEquipment>(EquipmentClass, transform, InOwnerCharacter);
		equipment->SetData(EquipmentData);
		equipment->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "Equipment"));
		UGameplayStatics::FinishSpawningActor(equipment, transform);

		if (!!attachment)
		{
			equipment->OnBeginEquip.AddDynamic(attachment, &AAttachment::OnEquip);
			equipment->OnUnequip.AddDynamic(attachment, &AAttachment::OnUnequip);
		}
	}

	ADoAction* doAction = nullptr;
	if (!!DoActionClass)
	{
		doAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ADoAction>(DoActionClass, transform, InOwnerCharacter);
		doAction->SetDatas(DoActionDatas);
		doAction->SetActorLabel(GetCustomActorLabel(InOwnerCharacter, "DoAction"));
		UGameplayStatics::FinishSpawningActor(doAction, transform);

		if (!!equipment)
		{
			doAction->SetEquippedThis(equipment->IsEquippedThis());
		}
		if (!!attachment)
		{
			attachment->OnBeginOverlap.AddDynamic(doAction, &ADoAction::OnBeginOverlap);
			attachment->OnEndOverlap.AddDynamic(doAction, &ADoAction::OnEndOverlap);
		}
	}

	(*OutSpawned) = NewObject<UActionData_Spawned>();
	(*OutSpawned)->Attachment = attachment;
	(*OutSpawned)->Equipment = equipment;
	(*OutSpawned)->DoAction = doAction;
}

FString UActionData::GetCustomActorLabel(ACharacter* InOwnerCharacter, FString ImMiddleName)
{
	FString name;
	name.Append(InOwnerCharacter->GetActorLabel());
	name.Append("_");
	name.Append(ImMiddleName);
	name.Append("_");
	name.Append(GetName().Replace(L"DA_", L""));

	return name;
}
