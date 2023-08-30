#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
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
	void OnSprint();
	void OffSprint();

private: // SpringArm
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

protected: // Camera
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly)
		class UCameraComponent* Camera;

};
