#include "PlayerAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* ownerPawn = TryGetPawnOwner();
	CheckNull(ownerPawn);

	UActionComponent* actionComp = CHelpers::GetComponent<UActionComponent>(ownerPawn);
	CheckNull(actionComp);

	actionComp->OnActionTypeChanged.AddDynamic(this, &UPlayerAnimInstance::OnActionTypeChanged);
	actionComp->OnDoSubAction.AddDynamic(this, &UPlayerAnimInstance::OnDoSubAction);

	UStateComponent* stateComp = CHelpers::GetComponent<UStateComponent>(ownerPawn);
	CheckNull(stateComp);

	stateComp->OnStateTypeChanged.AddDynamic(this, &UPlayerAnimInstance::OnStateTypeChanged);
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSecnods)
{
	Super::NativeUpdateAnimation(DeltaSecnods);

	APawn* ownerPawn = TryGetPawnOwner();
	CheckNull(ownerPawn);

	Speed = ownerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(ownerPawn->GetVelocity(), ownerPawn->GetActorRotation());
	bIsFalling = Cast<ACharacter>(ownerPawn)->GetMovementComponent()->IsFalling();
}

void UPlayerAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}

void UPlayerAnimInstance::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	StateType = InNewType;
}

void UPlayerAnimInstance::OnDoSubAction(bool InSubAction)
{
	bSubAction = InSubAction;
}