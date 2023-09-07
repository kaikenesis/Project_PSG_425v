#include "HUDWidget.h"
#include "Global.h"
#include "BuildingMenuWidget.h"

void UHUDWidget::ShowBuildingMenu()
{
	CheckNull(BuildingMenu);
	if (BuildingMenu->IsVisible())
	{
		BuildingMenu->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHUDWidget::HideBuildingMenu()
{
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
