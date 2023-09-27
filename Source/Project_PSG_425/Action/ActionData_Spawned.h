#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionData_Spawned.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		FName StartSection;

	UPROPERTY(EditAnywhere)
		bool bCanMove = true;

	UPROPERTY(EditAnywhere)
		bool bLookForward = true;
	// bUseControlRoationYaw = true
	// bOrientRotationToMovement = false

};

USTRUCT(BlueprintType)
struct FDoActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Power = 1.f;

	UPROPERTY(EditAnywhere)
		float HitStop; // global time세팅을 통해서 느려지게하거나 멈추게 하는 값

	UPROPERTY(EditAnywhere)
		class UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
		FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShake> ShakeClass;

	//UPROPERTY(EditAnywhere)
	//	TSubclassOf<class ACMagicBall> ProjectileClass;
};

UCLASS()
class PROJECT_PSG_425_API UActionData_Spawned : public UObject
{
	GENERATED_BODY()
	
public:
	friend class UActionData;

public:
	FORCEINLINE class AEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE class AAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE class ADoAction* GetDoAction() { return DoAction; }

private:
	class AEquipment* Equipment;
	class AAttachment* Attachment;
	class ADoAction* DoAction;
};
