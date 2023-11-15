#include "AnimNotify_Hitted.h"
#include "Global.h"
#include "Components/StateComponent.h"

FString UAnimNotify_Hitted::GetNotifyName_Implementation() const
{
	return "Hitted";
}

void UAnimNotify_Hitted::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UStateComponent* stateComp = CHelpers::GetComponent<UStateComponent>(MeshComp->GetOwner());
	CheckNull(stateComp);

	stateComp->SetIdleMode();
}
