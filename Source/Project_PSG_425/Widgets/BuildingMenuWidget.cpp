#include "BuildingMenuWidget.h"
#include "DataTable/CustomDataTables.h"
#include "Global.h"

void UBuildingMenuWidget::PreConstruct(bool IsDesignTime)
{
	Super::PreConstruct(IsDesignTime);
	//if (IsDesignTime == true)
		
}

void UBuildingMenuWidget::Construct()
{
	Super::Construct();

}

void UBuildingMenuWidget::Tick(FGeometry MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);

}

void UBuildingMenuWidget::ConstructWidget(bool Success)
{
	CurrentBuildingList = DefaultBuildingList;
	CurrentBuildingDataTable = DefaultBuildingDataTable;

	UpdateWidget(Success);

}

void UBuildingMenuWidget::UpdateWidget(bool Success)
{
	bool result;

	MaxSegmentCount = FMath::Clamp(MaxSegmentCount, 3, 16);

	if (!!CurrentBuildingList.DataTable)
	{
		if (CurrentBuildingList.RowName != FName("None"))
			result = true;
		else
			result = false;
	}
	else
		result = false;

	if (result == true)
	{
		UpdateBuildingList(CurrentBuildingList);
		Success = true;
	}
	else
	{
		UpdateBuildingDataTable(CurrentBuildingDataTable);
		Success = true;
	}
	
}

void UBuildingMenuWidget::UpdateBuildingList(FDataTableRowHandle InBuildingListHandle, bool Success)
{
	MaxSegmentCount = FMath::Clamp(MaxSegmentCount, 3, 16);
	
	if (!!InBuildingListHandle.DataTable)
	{
		BuildingObjects = InBuildingListHandle.DataTable->FindRow<FBuildingList>(InBuildingListHandle.RowName, "")->BuildingObjects;
	}

	//UpdateSegment();
	Success = true;
}

void UBuildingMenuWidget::UpdateBuildingDataTable(UDataTable* InDataTable, bool Success)
{
	
}
