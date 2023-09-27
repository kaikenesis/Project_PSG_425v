#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActionData.h"
#include "Equipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginEquipSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipSignature);

UCLASS()
class PROJECT_PSG_425_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquipment();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetData(FEquipmentData& InData) { Data = InData; }
	FORCEINLINE const bool* IsEquippedThis() { return &bEquippedThis; } // 주소를 반환해서 호출된곳에서 원본값을 즉시 수정할 수 있도록함

public:
	//Play DrawMontage
	UFUNCTION(BlueprintNativeEvent)
		void Equip();
	void Equip_Implementation();

	//Attach to hand socket
	UFUNCTION(BlueprintNativeEvent)
		void Begin_Equip();
	void Begin_Equip_Implementation();

	//Set State Idle
	UFUNCTION(BlueprintNativeEvent)
		void End_Equip();
	void End_Equip_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void Unequip();
	void Unequip_Implementation();

public:
	UPROPERTY(BlueprintAssignable)
		FBeginEquipSignature OnBeginEquip;

	UPROPERTY(BlueprintAssignable)
		FUnequipSignature OnUnequip;

protected:
	UPROPERTY(BlueprintReadOnly)
		class ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
		class UStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly)
		class UStatusComponent* StatusComp;

private:
	FEquipmentData Data;
	bool bEquippedThis;

};
