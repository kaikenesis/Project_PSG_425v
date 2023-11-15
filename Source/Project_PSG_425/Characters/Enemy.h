#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StateComponent.h"
#include "Enemy.generated.h"

UCLASS()
class PROJECT_PSG_425_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void Hitted();
	void Dead();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private: //Scene Component
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

protected: //Actor Component
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UActionComponent* Action;

private: //Actor Component
	UPROPERTY(VisibleDefaultsOnly)
		class UMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UStateComponent* State;

private:
	UPROPERTY(EditAnywhere)
		float LaunchValue = 25.f;

private:
	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;

};
