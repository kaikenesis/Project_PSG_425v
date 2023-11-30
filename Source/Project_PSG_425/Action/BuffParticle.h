#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffParticle.generated.h"

UCLASS()
class PROJECT_PSG_425_API ABuffParticle : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuffParticle();

public:
	FORCEINLINE UParticleSystemComponent* Get() { return Particle; }

	void Play(float InTime);

	UFUNCTION()
		void Finish();
	UFUNCTION()
		void Destroy();

private:
	USceneComponent* Root;
	UParticleSystemComponent* Particle;

};
