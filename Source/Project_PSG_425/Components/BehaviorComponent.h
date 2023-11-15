#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait,
	Approach,
	Action,
	Patrol,
	Hitted
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChangedSignature, EBehaviorType, InPrevType, EBehaviorType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PSG_425_API UBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBehaviorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }

public: //Get Behavior from BB
	UFUNCTION(BlueprintCallable)
		bool IsWaitMode();
		
	UFUNCTION(BlueprintCallable)
		bool IsApproachMode();

	UFUNCTION(BlueprintCallable)
		bool IsAcionMode();

	UFUNCTION(BlueprintCallable)
		bool IsPatrolMode();

	UFUNCTION(BlueprintCallable)
		bool IsHittedMode();

private:
	EBehaviorType GetTypeFromBB();

public: //Set Behavior to BB
	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetHittedMode();

	class APlayerCharacter* GetPlayerKey();
	FVector GetLocationKey();

private:
	void ChangeType(EBehaviorType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
		FBehaviorTypeChangedSignature OnBehaviorTypeChanged;

private:
	UPROPERTY(EditAnywhere)
		FName BehaviorKey = "BehaviorKey";

	UPROPERTY(EditAnywhere)
		FName PlayerKey = "PlayerKey";

	UPROPERTY(EditAnywhere)
		FName LocationKey = "LocationKey";

private:
	class UBlackboardComponent* Blackboard;
};
