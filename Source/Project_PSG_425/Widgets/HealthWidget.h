#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

UCLASS()
class PROJECT_PSG_425_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
		void UpdateHealth(float InCurrentHealth, float InMaxHealth);
	void UpdateHealth_Implementation(float InCurrentHealth, float InMaxHealth);

private:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
};
