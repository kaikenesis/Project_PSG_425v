#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/IBuildingWidget.h"
#include "HUDWidget.generated.h"

UCLASS()
class PROJECT_PSG_425_API UHUDWidget : public UUserWidget, public IIBuildingWidget
{
	GENERATED_BODY()
	
public:
	void ShowBuildingMenu();
	void HideBuildingMenu();

public:
	virtual void ShowBuildingMenu_Interface() override;
	virtual void HideBuildingMenu_Interface() override;

private:
	UPROPERTY(meta = (BindWidget))
		class UBuildingMenuWidget* BuildingMenu;
};
