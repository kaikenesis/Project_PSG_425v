#include "AnimNotify_BeginAction.h"
#include "Global.h"
#include "Components/ActionComponent.h"
#include "Action/ActionData.h"
#include "Action/DoAction.h"

FString UAnimNotify_BeginAction::GetNotifyName_Implementation() const
{
	return "BeginAction";
}

void UAnimNotify_BeginAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	UActionData_Spawned* currentData = actionComp->GetCurrentData();
	CheckNull(currentData);

	ADoAction* doAction = currentData->GetDoAction();
	CheckNull(doAction);

	doAction->Begin_DoAction();
}
