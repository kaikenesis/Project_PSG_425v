#include "PlayerCharacter.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimInstance/PlayerAnimInstance.h"
#include "Components/BuildingComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Component
	CHelpers::CreateSceneComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateSceneComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	//Component Settings
	//<Mesh>
	USkeletalMesh* skeletalMesh;
	CHelpers::GetAsset<USkeletalMesh>(&skeletalMesh, "SkeletalMesh'/Game/Characters/Mannequin/Mesh/SK_Mannequin.SK_Mannequin'");
	if(!!skeletalMesh)
		GetMesh()->SetSkeletalMesh(skeletalMesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<class UPlayerAnimInstance> animClass;
	CHelpers::GetClass<UPlayerAnimInstance>(&animClass, "AnimBlueprint'/Game/Characters/Mannequin/Animations/ABP_Player.ABP_Player_C'");
	if(!!animClass)
		GetMesh()->SetAnimClass(animClass);

	//<Movement>
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	 
	//<SpringArm>
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
}

void APlayerCharacter::BeginPlay()
{
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
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::OnSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::OffSprint);
}

void APlayerCharacter::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void APlayerCharacter::OnMoveRight(float Axis)
{
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

void APlayerCharacter::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void APlayerCharacter::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}