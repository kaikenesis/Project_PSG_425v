#include "AnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/ActionComponent.h"
#include "Action/ActionData.h"
#include "Action/Attachment.h"
#include "Action/DoAction_Melee.h"

FString UAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	AAttachment* attachment = currentData->GetAttachment();
	CheckNull(attachment);

	attachment->OnCollisions();
}

void UAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	AAttachment* attachment = currentData->GetAttachment();
	CheckNull(attachment);

	attachment->OffCollisions();

	ADoAction_Melee* doAction_melee = Cast<ADoAction_Melee>(currentData->GetDoAction());
	CheckNull(doAction_melee);
	doAction_melee->ClearHittedCharacters();
}
