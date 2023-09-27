#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionData.h"
#include "DoAction.generated.h"

UCLASS()
class PROJECT_PSG_425_API ADoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoAction();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE void SetDatas(TArray<FDoActionData> InDatas) { Datas = InDatas; }
	FORCEINLINE void SetEquippedThis(const bool* InEquippedThis) { bEquippedThis = InEquippedThis; }

	virtual void DoAction() {}
	virtual void Begin_DoAction() {}
	virtual void End_DoAction() {}

public:
	UFUNCTION()
		virtual void OnBeginOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {}

	UFUNCTION()
		virtual void OnEndOverlap(class ACharacter* InAttacker, class AActor* InCauser, class ACharacter* InOtherCharacter) {}

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly)
		class UStatusComponent* StatusComp;

protected:
	TArray<FDoActionData> Datas;
	const bool* bEquippedThis;

};
