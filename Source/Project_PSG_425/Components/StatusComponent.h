#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

UENUM(BlueprintType)
enum class EWalkSpeedType : uint8
{
	Sneak,
	Walk,
	Sprint,
	Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_PSG_425_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetSneakSpeed() { return WalkSpeed[(int32)EWalkSpeedType::Sneak]; }
	FORCEINLINE float GetWalkSpeed() { return WalkSpeed[(int32)EWalkSpeedType::Walk]; }
	FORCEINLINE float GetSprintSpeed() { return WalkSpeed[(int32)EWalkSpeedType::Sprint]; }

	FORCEINLINE bool IsCanMove() { return bCanMove; }

	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }

	FORCEINLINE bool IsDead() { return CurrentHealth <= 0; }

	void SetMove();
	void SetStop();
	void ChangeMoveSpeed(EWalkSpeedType InType);

	void IncreaseHealth(float InAmount);
	void DecreaseHealth(float InAmount);

public: // Abnormality Func
	void PlayBurn(float InTickTime, int32 InTickCount, float TickDamage, FTransform InTransform, bool IsLoop = false, class UParticleSystem* InParticle = nullptr);
	void PlayEffect(class UParticleSystem* InParticle, FTransform InTransform, float InTime);

private:
	void UpdateHealthWidget();

	UFUNCTION()
		void Burn();

	FORCEINLINE void SetBurnCount(int32 InTickCount) { BurnCount = InTickCount; }
	FORCEINLINE void SetBurnTickDamage(float TickDamage) { BurnTickDamage = TickDamage; }
	FORCEINLINE void SetBurnDebuff(class ABuffParticle* InBuff) { BurnDebuff = InBuff; }

private:
	UPROPERTY(EditAnywhere, Category = "Speed")
		float WalkSpeed[(int32)EWalkSpeedType::Max] = { 200.f, 400.f, 600.f };

	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100.f;

private: // Abnormality Val
	UPROPERTY(EditAnywhere, Category = "Abnormality")
		bool BurnImmune;

	int32 BurnCount = 0;
	float BurnTickDamage = 0.f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABuffParticle> ParticleClass;

	class ABuffParticle* BurnDebuff = nullptr;

private:
	bool bCanMove = true;
	float CurrentHealth;

	class ACharacter* OwnerCharacter;
	class UStateComponent* StateComp;
	class UHealthWidget* HealthWidget;
};
