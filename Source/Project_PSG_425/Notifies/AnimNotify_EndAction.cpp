#include "AnimNotify_EndAction.h"
#include "Global.h"
#include "Components/ActionComponent.h"
#include "Action/ActionData.h"
#include "Action/DoAction.h"

FString UAnimNotify_EndAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UAnimNotify_EndAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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

	doAction->End_DoAction();
}
