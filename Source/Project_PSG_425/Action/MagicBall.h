#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicBall.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMagicBallBeginOverlapSignature, FHitResult, InHitResult);

UCLASS()
class PROJECT_PSG_425_API AMagicBall : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicBall();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintAssignable)
		FMagicBallBeginOverlapSignature OnBeginOverlap;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Impact")
		class UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Impact")
		FTransform ImpactTransform;

};
