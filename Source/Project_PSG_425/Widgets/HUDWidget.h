#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/IBuildingWidget.h"
#include "HUDWidget.generated.h"

UCLASS()
class PROJECT_PSG_425_API UHUDWidget : public UUserWidget, public IIBuildingWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void ShowBuildingMenu();
	void HideBuildingMenu();

public: // 인터페이스 콜
	virtual void ShowBuildingMenu_Interface() override;
	virtual void HideBuildingMenu_Interface() override;

public: // 딜리게이트 바인드
	UFUNCTION()
		void OnBuildingSegmentClicked(class UBuildingMenuSegmentWidget* InBuildingMenuSegmentWidget);

private:
	UPROPERTY(meta = (BindWidget))
		class UBuildingMenuWidget* BuildingMenu;
};
