#pragma once

#include "CoreMinimal.h"
#include "Action/DoAction.h"
#include "Components/ActionComponent.h"
#include "DoAction_MagicBall.generated.h"

UCLASS()
class PROJECT_PSG_425_API ADoAction_MagicBall : public ADoAction
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;

	virtual void OnAim() override;
	virtual void OffAim() override;

private:
	UFUNCTION()
		void OnMagicBallBeginOverlap(FHitResult InHitResult);

	UFUNCTION()
		void AbortByTypeChanged(EActionType InPrevType, EActionType InNewType);

private:
	UPROPERTY()
		class UAim* Aim;

	UActionComponent* ActionComp;
};
