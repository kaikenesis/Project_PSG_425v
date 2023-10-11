#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NameWidget.generated.h"

UCLASS()
class PROJECT_PSG_425_API UNameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
		void SetNames(const FString& InControllerName, const FString& InPawnName);
	void SetNames_Implementation(const FString& InControllerName, const FString& InPawnName);

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ControllerName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* PawnName;

};
