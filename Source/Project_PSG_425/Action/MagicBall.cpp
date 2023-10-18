#include "MagicBall.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "particles/ParticleSystemComponent.h"

AMagicBall::AMagicBall()
{
	CHelpers::CreateSceneComponent(this, &Sphere, "Sphere");
	CHelpers::CreateSceneComponent(this, &Particle, "Particle", Sphere);

	CHelpers::CreateActorComponent(this, &Projectile, "Projectile");

	InitialLifeSpan = 5.f;

	Projectile->InitialSpeed = 2000.f;
	Projectile->MaxSpeed = 4000.f;
	Projectile->ProjectileGravityScale = 0.f;
}

void AMagicBall::BeginPlay()
{
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMagicBall::OnComponentBeginOverlap);

	Super::BeginPlay();
	
}

void AMagicBall::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == GetOwner());

	//Play Impact Particle
	if (ImpactParticle)
	{
		FTransform transform = ImpactTransform;
		transform.AddToTranslation(GetActorLocation());
		transform.SetRotation(SweepResult.ImpactNormal.ToOrientationQuat());

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, transform);
	}

	if (OnBeginOverlap.IsBound())
		OnBeginOverlap.Broadcast(SweepResult);

	Destroy();
}

