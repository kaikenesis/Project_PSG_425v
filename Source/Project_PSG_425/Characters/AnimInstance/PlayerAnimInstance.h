#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/ActionComponent.h"
#include "Components/StateComponent.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class PROJECT_PSG_425_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSecnods) override;

private:
	UFUNCTION()
		void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void OnDoSubAction(bool InSubAction);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool bSubAction;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		EActionType ActionType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		EStateType StateType;

};
