#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "Aim.generated.h"

UCLASS()
class PROJECT_PSG_425_API UAim : public UObject
{
	GENERATED_BODY()
	
public:
	UAim();

	void BeginPlay(class ACharacter* InOwnerCharacter);
	void Tick(float DeltaTime);

public:
	FORCEINLINE bool IsAvailable() { return SpringArm != nullptr && Camera != nullptr; } // 스프링암, 카메라를 가지고 있는지 == 플레이어인지
	FORCEINLINE bool IsZooming() { return bZooming; }

	void On();
	void Off();

private:
	UFUNCTION()
		void Zooming(float Output);

private:
	class ACharacter* OwnerCharacter;
	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	bool bZooming;

	class UCurveFloat* Curve;
	FTimeline Timeline;
	FOnTimelineFloat OnTimeline;
};
