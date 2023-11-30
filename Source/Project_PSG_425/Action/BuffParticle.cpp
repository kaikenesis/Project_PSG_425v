#include "BuffParticle.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"

ABuffParticle::ABuffParticle()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Root);
}

void ABuffParticle::Play(float InTime)
{
	UKismetSystemLibrary::K2_SetTimer(this, "Finish", InTime, false);
}

void ABuffParticle::Finish()
{
	Particle->SetActive(false, false);

	UKismetSystemLibrary::K2_SetTimer(this, "Destroy", 5.f, false);
}

void ABuffParticle::Destroy()
{
	AActor::Destroy();
}
