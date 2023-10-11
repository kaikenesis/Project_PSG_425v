#include "Enemy.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BuildingComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ActionComponent.h"
#include "Components/MontagesComponent.h"
#include "Components/CapsuleComponent.h"
#include "Widgets/NameWidget.h"
#include "Widgets/HealthWidget.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create Scene Component
	CHelpers::CreateSceneComponent(this, &NameWidget, "NameWidget", GetMesh());
	CHelpers::CreateSceneComponent(this, &HealthWidget, "HealthWidget", GetMesh());

	// Create Actor Component
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
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

	//<Movement Comp>
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
	GetCharacterMovement()->JumpZVelocity = 600.f;

	//<Widget Comp>
	TSubclassOf<UNameWidget> nameWidgetClass;
	CHelpers::GetClass(&nameWidgetClass, "/Game/Widgets/WB_Name");
	NameWidget->SetWidgetClass(nameWidgetClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 220));
	NameWidget->SetDrawSize(FVector2D(240, 50));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<UHealthWidget> healthWidgetClass;
	CHelpers::GetClass(&healthWidgetClass, "/Game/Widgets/WB_Health");
	HealthWidget->SetWidgetClass(healthWidgetClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 180));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void AEnemy::BeginPlay()
{
	State->OnStateTypeChanged.AddDynamic(this, &AEnemy::OnStateTypeChanged);

	Super::BeginPlay();
	
	//Widget Settings
	NameWidget->InitWidget();
	UNameWidget* nameWidget = Cast<UNameWidget>(NameWidget->GetUserWidgetObject());
	if (!!nameWidget)
	{
		nameWidget->SetNames(GetController()->GetName(), GetName());
	}

	HealthWidget->InitWidget();
	UHealthWidget* healthWidget = Cast<UHealthWidget>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidget)
	{
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());
	}
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
	//Apply Health Widget
	UHealthWidget* healthWidget = Cast<UHealthWidget>(HealthWidget->GetUserWidgetObject());
	if (!!healthWidget)
	{
		CLog::Print("UpdateHealthWidget");
		healthWidget->UpdateHealth(Status->GetCurrentHealth(), Status->GetMaxHealth());
	}

	//Play Hitted Montage
	Montages->PlayHitted();

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
	//Widget Visibility Disable
	NameWidget->SetVisibility(false);
	HealthWidget->SetVisibility(false);

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

