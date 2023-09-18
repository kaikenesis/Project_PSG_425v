#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PSG_425_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetSneakSpeed() { return SneakSpeed; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed; }
	FORCEINLINE float GetSprintSpeed() { return SprintSpeed; }

	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }

	FORCEINLINE bool IsDead() { return CurrentHealth <= 0; }

	void SetMove();
	void SetStop();

	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float SneakSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float WalkSpeed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Speed")
		float SprintSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100.f;

private:
	bool bCanMove = true;
	float CurrentHealth;
};
