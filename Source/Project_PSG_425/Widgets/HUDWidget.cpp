#include "HUDWidget.h"
#include "Global.h"
#include "BuildingMenuWidget.h"
#include "BuildingMenuSegmentWidget.h"
#include "Game/CraftRPGPlayerController.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BuildingMenu->OnBuildingSegmentClicked.AddDynamic(this, &UHUDWidget::OnBuildingSegmentClicked);
}

void UHUDWidget::ShowBuildingMenu()
{
	CheckNull(BuildingMenu);
	if (!BuildingMenu->IsVisible())
	{
		BuildingMenu->SetVisibility(ESlateVisibility::Visible);
		GetOwningPlayer()->bShowMouseCursor = true;
		FInputModeGameAndUI inputMode;
		GetOwningPlayer()->SetInputMode(inputMode);
	}
}

void UHUDWidget::HideBuildingMenu()
{
	CheckNull(BuildingMenu);
	if (BuildingMenu->IsVisible())
	{
		BuildingMenu->SetVisibility(ESlateVisibility::Hidden);
		GetOwningPlayer()->bShowMouseCursor = false;
		FInputModeGameOnly inputMode;
		GetOwningPlayer()->SetInputMode(inputMode);
	}
}

//Interface
void UHUDWidget::ShowBuildingMenu_Interface()
{
	ShowBuildingMenu();
}

void UHUDWidget::HideBuildingMenu_Interface()
{
	HideBuildingMenu();
}

void UHUDWidget::OnBuildingSegmentClicked(UBuildingMenuSegmentWidget* InBuildingMenuSegmentWidget)
{
	HideBuildingMenu();
	Cast<ACraftRPGPlayerController>(GetOwningPlayer())->TryStartBuildObject_Interface(InBuildingMenuSegmentWidget->BuildingObjectHandle);
}
