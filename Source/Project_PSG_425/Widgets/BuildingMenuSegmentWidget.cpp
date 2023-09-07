#include "BuildingMenuSegmentWidget.h"

bool UBuildingMenuSegmentWidget::UpdateWidget()
{
	if (BuildingObjectHandle.DataTable != nullptr)
	{
		BuildingObjectSettings = BuildingObjectHandle.DataTable->FindRow<FBuildingObjectSettings>(BuildingObjectHandle.RowName, "");
		IconTexture = BuildingObjectSettings->Icon;
	}

	return Super::UpdateWidget();
}