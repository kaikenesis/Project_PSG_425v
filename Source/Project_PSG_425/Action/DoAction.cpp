#include "DoAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/StateComponent.h"
#include "Components/StatusComponent.h"

ADoAction::ADoAction()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADoAction::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	StateComp = CHelpers::GetComponent<UStateComponent>(OwnerCharacter);
	StatusComp = CHelpers::GetComponent<UStatusComponent>(OwnerCharacter);

	Super::BeginPlay();
	
}

void ADoAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

