#include "PlayerCharacter.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Game/CraftRPGPlayerController.h"
#include "Components/BuildingComponent.h"
#include "Components/StatusComponent.h"
#include "Components/StateComponent.h"
#include "Components/ActionComponent.h"
#include "Components/MontagesComponent.h"
#include "Components/CapsuleComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Scene Component
	CHelpers::CreateSceneComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateSceneComponent(this, &Camera, "Camera", SpringArm);

	// Create Actor Component
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &State, "State");

	//Component Settings
	//<Mesh Comp>
	USkeletalMesh* skeletalMesh;
	CHelpers::GetAsset<USkeletalMesh>(&skeletalMesh, "SkeletalMesh'/Game/Blueprints/Characters/Player/Mesh/SK_Sci_Fi_Character_08_Full_02.SK_Sci_Fi_Character_08_Full_02'");
	if(!!skeletalMesh)
		GetMesh()->SetSkeletalMesh(skeletalMesh);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	//<Movement Comp>
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
	GetCharacterMovement()->JumpZVelocity = 600.f;
	
	//<SpringArm Comp>
	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bDoCollisionTest = false;
}

void APlayerCharacter::BeginPlay()
{
	ACraftRPGPlayerController* controller = Cast<ACraftRPGPlayerController>(GetController());
	if(!!controller)
		BuildComp = CHelpers::GetComponent<UBuildingComponent>(controller);


	State->OnStateTypeChanged.AddDynamic(this, &APlayerCharacter::OnStateTypeChanged);

	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis Event
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizentalLook", this, &APlayerCharacter::OnHorizentalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &APlayerCharacter::OnVerticalLook);

	//Action Event
	PlayerInputComponent->BindAction("Jump", IE_Pressed , this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &APlayerCharacter::OnWalk);
	PlayerInputComponent->BindAction("Walk", IE_Released, this, &APlayerCharacter::OffWalk);
	PlayerInputComponent->BindAction("OneHandShield", IE_Pressed, this, &APlayerCharacter::OnOneHandShield);
	PlayerInputComponent->BindAction("TwoHand", IE_Pressed, this, &APlayerCharacter::OnTwoHand);
	PlayerInputComponent->BindAction("MagicBall", IE_Pressed, this, &APlayerCharacter::OnMagicBall);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &APlayerCharacter::OnAction);
	PlayerInputComponent->BindAction("SubAction", IE_Pressed, this, &APlayerCharacter::OnSubAction);
	PlayerInputComponent->BindAction("SubAction", IE_Released, this, &APlayerCharacter::OffSubAction);
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());
	Causer = DamageCauser;

	Action->AbortByDamaged();
	Status->DecreaseHealth(DamageValue);

	if (Status->IsDead())
	{
		State->SetDeadMode();
		return DamageValue;
	}

	if (Action->IsSubAction())
	{
		State->SetBlockMode();
		return DamageValue;
	}

	State->SetHittedMode();
	return DamageValue;
}

void APlayerCharacter::OnOneHandShield()
{
	CheckFalse(State->IsIdleMode());

	Action->SetOneHandShieldMode();
}

void APlayerCharacter::OnTwoHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetTwoHandMode();
}

void APlayerCharacter::OnMagicBall()
{
	CheckFalse(State->IsIdleMode());

	Action->SetMagicBallMode();
}

void APlayerCharacter::OnAction()
{
	CheckTrue(BuildComp->IsBuildMode());

	Action->DoAction();
}

void APlayerCharacter::OnSubAction()
{
	CheckTrue(BuildComp->IsBuildMode());

	Action->SetSubAction(true);

	GetCharacterMovement()->MaxWalkSpeed = Status->GetWalkSpeed();
}

void APlayerCharacter::OffSubAction()
{
	CheckTrue(BuildComp->IsBuildMode());

	Action->SetSubAction(false);

	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
}

void APlayerCharacter::Blocked()
{
	CLog::Print("Block");
	Montages->PlayBlock();
}

void APlayerCharacter::Hitted()
{
	CLog::Print("Hit");
	Montages->PlayHitted();
}

void APlayerCharacter::Dead()
{
	CheckFalse(State->IsDeadMode());

	APlayerController* controller = GetController<APlayerController>();
	if (!!controller)
		DisableInput(controller);

	Montages->PlayDead();

	Action->OffAllCollisions();
	GetCapsuleComponent()->SetCollisionProfileName("Spectator");

	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 5.f, false);
}

void APlayerCharacter::End_Dead()
{
	Action->End_Dead();
}

void APlayerCharacter::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Block:		Blocked();	break;
	case EStateType::Hitted:	Hitted();	break;
	case EStateType::Dead:		Dead();		break;
	}
}

void APlayerCharacter::OnMoveForward(float Axis)
{
	CheckTrue(FMath::IsNearlyZero(Axis));
	CheckFalse(Status->IsCanMove());
	CheckTrue(Action->IsTwoHandMode() && Action->IsSubAction());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void APlayerCharacter::OnMoveRight(float Axis)
{
	CheckTrue(FMath::IsNearlyZero(Axis));
	CheckFalse(Status->IsCanMove());
	CheckTrue(Action->IsTwoHandMode() && Action->IsSubAction());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, Axis);
}

void APlayerCharacter::OnHorizentalLook(float Axis)
{
	AddControllerYawInput(Axis);
}

void APlayerCharacter::OnVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis);
}

void APlayerCharacter::OnWalk()
{
	CheckTrue(Action->IsSubAction());
	Status->ChangeMoveSpeed(EWalkSpeedType::Walk);
}

void APlayerCharacter::OffWalk()
{
	CheckTrue(Action->IsSubAction());
	Status->ChangeMoveSpeed(EWalkSpeedType::Sprint);
}

FGenericTeamId APlayerCharacter::GetGenericTeamId() const
{
	return FGenericTeamId(PlayerTeamID);
}