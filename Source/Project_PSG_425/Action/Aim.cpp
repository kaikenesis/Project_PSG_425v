#include "Aim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

UAim::UAim()
{
	CHelpers::GetAsset<UCurveFloat>(&Curve, "/Game/Blueprints/Action/Player/Curve_Aim");
}

void UAim::BeginPlay(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	OnTimeline.BindUFunction(this, "Zooming");
	Timeline.AddInterpFloat(Curve, OnTimeline);
	Timeline.SetPlayRate(5.f);

	UWorld* wolrd = OwnerCharacter->GetWorld();
	CheckNull(wolrd);
}

void UAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UAim::On()
{
	CheckFalse(IsAvailable());
	CheckTrue(bZooming);

	bZooming = true;

	SpringArm->TargetArmLength = 150.f;
	SpringArm->SocketOffset = FVector(0, 40, 10);
	SpringArm->bEnableCameraLag = false;

	Timeline.Play();
}

void UAim::Off()
{
	CheckFalse(IsAvailable());
	CheckFalse(bZooming);

	bZooming = false;

	SpringArm->TargetArmLength = 200.f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true;

	Timeline.ReverseFromEnd();
}

void UAim::Zooming(float Output)
{
	Camera->FieldOfView = Output;
}
