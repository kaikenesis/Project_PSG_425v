#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StateComponent.h"
#include "GenericTeamAgentInterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECT_PSG_425_API APlayerCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual FGenericTeamId GetGenericTeamId() const override;

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
	void Blocked();
	void Hitted();
	void Dead();

	UFUNCTION()
		void End_Dead();

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
		class UMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UStateComponent* State;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
		uint8 PlayerTeamID = 0;

private:
	class UBuildingComponent* BuildComp;
	FGenericTeamId TeamGenericID;

	float DamageValue;
	class ACharacter* Attacker;
	class AActor* Causer;
};
