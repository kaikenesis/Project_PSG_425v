#include "Attachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

AAttachment::AAttachment()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
}

void AAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	GetComponents<UShapeComponent>(Collisions);

	for (const auto& collision : Collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this, &AAttachment::BeginOverlap);
		collision->OnComponentEndOverlap.AddDynamic(this, &AAttachment::EndOverlap);
	}

	OffCollisions();

	Super::BeginPlay();
}

void AAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void AAttachment::AttachToComp(USceneComponent* InComponent, FName InSocketName)
{
	InComponent->AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		InSocketName
	);
}

void AAttachment::OnCollisions()
{
	for (const auto& collision : Collisions)
		collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AAttachment::OffCollisions()
{
	for (const auto& collision : Collisions)
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAttachment::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);

	ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);

	if (OnBeginOverlap.IsBound())
	{
		if (!!otherCharacter)
			OnBeginOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
	}
}

void AAttachment::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

