#include "AnimNotify_Blocked.h"
#include "Global.h"
#include "Components/StateComponent.h"
#include "Components/ActionComponent.h"

FString UAnimNotify_Blocked::GetNotifyName_Implementation() const
{
	return "Blocked";
}

void UAnimNotify_Blocked::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UStateComponent* stateComp = CHelpers::GetComponent<UStateComponent>(MeshComp->GetOwner());
	CheckNull(stateComp);

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(MeshComp->GetOwner());
	CheckNull(actionComp);

	stateComp->SetIdleMode();
}
