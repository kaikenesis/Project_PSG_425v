#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle,
	Roll,
	Evade,
	Equip,
	Action,
	Block,
	Hitted,
	Dead,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChangedSignature, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PSG_425_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public: //Get State
	FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	FORCEINLINE bool IsRollMode() { return Type == EStateType::Roll; }
	FORCEINLINE bool IsEvadeMode() { return Type == EStateType::Evade; }
	FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }
	FORCEINLINE bool IsActionMode() { return Type == EStateType::Action; }
	FORCEINLINE bool IsBlockMode() { return Type == EStateType::Block; }
	FORCEINLINE bool IsHittedMode() { return Type == EStateType::Hitted; }
	FORCEINLINE bool IsDeadMode() { return Type == EStateType::Dead; }

public: //Set State
	void SetIdleMode();
	void SetRollMode();
	void SetEvadeMode();
	void SetEquipMode();
	void SetActionMode();
	void SetBlockMode();
	void SetHittedMode();
	void SetDeadMode();

public:
	FORCEINLINE EStateType GetType() { return Type; }

private:
	void ChangeType(EStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FStateTypeChangedSignature OnStateTypeChanged;

private:
	EStateType Type;
		
};
