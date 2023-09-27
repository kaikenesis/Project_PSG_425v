#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Components/StateComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECT_PSG_425_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: // Axis Event
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnHorizentalLook(float Axis);
	void OnVerticalLook(float Axis);

private: // Action Event
	void OnWalk();
	void OffWalk();
	void OnOneHandShield();
	void OnTwoHand();
	void OnMagicBall();

	void OnAction();
	void OnSubAction();
	void OffSubAction();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private: //Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private: //Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UActionComponent* Action;

	UPROPERTY(VisibleDefaultsOnly)
		class UStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UStateComponent* State;
};
