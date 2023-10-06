#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "StateComponent.h"
#include "ActionComponent.h"
#include "MontagesComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EActionType ActionType;

	UPROPERTY(EditAnywhere)
		EStateType StateType;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PSG_425_API UMontagesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMontagesComponent();

protected:
	virtual void BeginPlay() override;

public:
	void PlayRoll();
	void PlayEvade();
	void PlayBlock();
	void PlayHitted();
	void PlayDead();
		
public:
	UFUNCTION()
		void ActionTypeChanged(EActionType InPrevType, EActionType InNewType);

	UFUNCTION()
		void DoSubAction(bool InSubAction);

private:
	void PlayAnimMontage(EActionType InActionType ,EStateType InStateType);

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		class UDataTable* DataTable;

private:
	FMontageData* Datas[(int32)EActionType::Max + (int32)EStateType::Max];
	EActionType CurrentActionType;
	bool IsSubAction;
};
