#include "Enemy.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BuildingComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ActionComponent.h"
#include "Components/CapsuleComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Actor Component
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");

	//Component Settings
	//<Mesh Comp>
	USkeletalMesh* skeletalMesh;
	CHelpers::GetAsset<USkeletalMesh>(&skeletalMesh, "SkeletalMesh'/Game/Blueprints/Characters/Mannequin/Mesh/SK_Mannequin.SK_Mannequin'");
	if (!!skeletalMesh)
		GetMesh()->SetSkeletalMesh(skeletalMesh);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	/*TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass(&animInstanceClass, "/Game/Characters/Mannequin/Animations/ABP_Player");
	if (!!animInstanceClass)
		GetMesh()->SetAnimInstanceClass(animInstanceClass);*/

	//<Movement Comp>
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
	GetCharacterMovement()->JumpZVelocity = 600.f;

	//<Widget Comp>
}

void AEnemy::BeginPlay()
{
	State->OnStateTypeChanged.AddDynamic(this, &AEnemy::OnStateTypeChanged);

	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	//Action->AbortByDamaged();
	Status->DecreaseHealth(DamageValue);

	if (Status->IsDead())
	{
		State->SetDeadMode();
		return DamageValue;
	}

	State->SetHittedMode();

	return DamageValue;
}

void AEnemy::Hitted()
{
	//Look At Attacker
	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FRotator rotation = FRotator(0, UKismetMathLibrary::FindLookAtRotation(start, target).Yaw, 0);
	SetActorRotation(rotation);

	//HitBack
	FVector direction = (start - target).GetSafeNormal2D();
	LaunchCharacter(direction * LaunchValue * DamageValue, true, false);
}

void AEnemy::Dead()
{
	//Ragdoll
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->GlobalAnimRateScale = 0.f;

	//Add Force
	FVector start = GetActorLocation();
	FVector target = Attacker->GetActorLocation();
	FVector direction = (start - target).GetSafeNormal2D();
	FVector force = direction * LaunchValue * DamageValue;
	GetMesh()->AddForceAtLocation(force, target);

	//Off All Collisions
	Action->OffAllCollisions();

	//Destroy All(Attachment, Equipment, DoAction...)
}

void AEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted:	Hitted();	break;
	case EStateType::Dead:		Dead();		break;
	}
}

