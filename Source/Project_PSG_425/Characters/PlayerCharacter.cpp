#include "PlayerCharacter.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BuildingComponent.h"
#include "Components/StatusComponent.h"
#include "Components/ActionComponent.h"
#include "Components/MontagesComponent.h"

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
	Action->DoAction();
}

void APlayerCharacter::OnSubAction()
{
	Action->SetSubAction(true);

	GetCharacterMovement()->MaxWalkSpeed = Status->GetWalkSpeed();
}

void APlayerCharacter::OffSubAction()
{
	Action->SetSubAction(false);

	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
}

void APlayerCharacter::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Roll:		Montages->PlayRoll();		break;
	case EStateType::Hitted:	Montages->PlayHitted();		break;
	case EStateType::Dead:		Montages->PlayDead();		break;
	}
}

void APlayerCharacter::OnMoveForward(float Axis)
{
	CheckFalse(Status->IsCanMove());
	CheckTrue(Action->IsTwoHandMode() && Action->IsSubAction());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void APlayerCharacter::OnMoveRight(float Axis)
{
	CheckFalse(Status->IsCanMove());
	CheckTrue(Action->IsTwoHandMode() && Action->IsSubAction());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

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
	GetCharacterMovement()->MaxWalkSpeed = Status->GetWalkSpeed();
}

void APlayerCharacter::OffWalk()
{
	CheckTrue(Action->IsSubAction());
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
}