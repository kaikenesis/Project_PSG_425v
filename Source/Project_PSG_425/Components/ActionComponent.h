#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed,
	OneHandShield,
	TwoHand,
	MagicBall,
	Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChangedSignature, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PSG_425_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActionComponent();

protected:
	virtual void BeginPlay() override;

public: //Get Action
	UFUNCTION(BlueprintPure)
		class UActionData* GetCurrentDataAsset() { return DataAssets[(int32)Type]; }

	UFUNCTION(BlueprintPure)
		class UActionData_Spawned* GetCurrentData() { return Datas[(int32)Type]; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsUnarmedMode() { return Type == EActionType::Unarmed; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsOneHandShieldMode() { return Type == EActionType::OneHandShield; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsTwoHandMode() { return Type == EActionType::TwoHand; }

	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsMagicBallMode() { return Type == EActionType::MagicBall; }

public: //Set Action
	void SetUnarmedMode();
	void SetOneHandShieldMode();
	void SetTwoHandMode();
	void SetMagicBallMode();

public:
	void DoAction();

	void OffAllCollisions();

private:
	void SetMode(EActionType InNewType);
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FActionTypeChangedSignature OnActionTypeChanged;

private:
	UPROPERTY(EditAnywhere)
		class UActionData* DataAssets[(int32)EActionType::Max];

private:
	EActionType Type;
		
	UPROPERTY()
		class UActionData_Spawned* Datas[(int32)EActionType::Max];
};
