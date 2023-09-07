#include "BuildingMenuWidget.h"
#include "DataTable/CustomDataTables.h"
#include "Global.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "BuildingMenuSegmentWidget.h"
#include "MenuSegmentWidget.h"

void UBuildingMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	ConstructWidget();
}

void UBuildingMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConstructWidget();
}

bool UBuildingMenuWidget::ConstructWidget()
{
	CurrentBuildingList = DefaultBuildingList;
	CurrentBuildingDataTable = DefaultBuildingDataTable;

	return UpdateWidget();

}

bool UBuildingMenuWidget::UpdateWidget()
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
		return true;
	}
	else
	{
		UpdateBuildingDataTable(CurrentBuildingDataTable);
		return true;
	}
	
}

bool UBuildingMenuWidget::UpdateBuildingList(FDataTableRowHandle InBuildingListHandle)
{
	MaxSegmentCount = FMath::Clamp(MaxSegmentCount, 3, 16);
	
	if (!!InBuildingListHandle.DataTable)
	{
		FBuildingList* buildingList = InBuildingListHandle.DataTable->FindRow<FBuildingList>(InBuildingListHandle.RowName, "");
		BuildingObjects = buildingList->BuildingObjects;
	}

	UpdateSegments();

	return true;
}

bool UBuildingMenuWidget::UpdateBuildingDataTable(UDataTable* InDataTable)
{
	if (!!InDataTable)
	{
		CurrentBuildingDataTable = InDataTable;
		TArray<FName> outRowNames = CurrentBuildingDataTable->GetRowNames();

		BuildingObjects.Empty();
		CLog::Print(BuildingObjects.Num());

		for (const auto& rowName : outRowNames)
		{
			FDataTableRowHandle dataTableRowHandle;
			dataTableRowHandle.DataTable = DefaultBuildingDataTable;
			dataTableRowHandle.RowName = rowName;

			BuildingObjects.Add(dataTableRowHandle);
		}
	}

	CurrentBuildingList.DataTable = nullptr;
	CurrentBuildingList.RowName = "";

	UpdateSegments();

	return true;
}

bool UBuildingMenuWidget::UpdateSegments()
{
	SegmentsCanvasPanel->ClearChildren();
	MenuSegments.Empty();
	bool addNextPage = false;
	bool addPrevPage = false;

	TArray<FDataTableRowHandle> resultBuildingObjects;
	CorrectPageDetails(BuildingObjects, resultBuildingObjects, addNextPage, addPrevPage);

	for (int i = 0; i < resultBuildingObjects.Num(); i++)
	{
		UBuildingMenuSegmentWidget* buildingMenuSegment = CreateWidget<UBuildingMenuSegmentWidget>(this);

		buildingMenuSegment->BuildingObjectHandle = resultBuildingObjects[i];
		buildingMenuSegment->SegmentIndex = i;
		buildingMenuSegment->SegmentCount = 16;
		
		MenuSegments.Add(buildingMenuSegment);
	}
	
	if (addPrevPage == true)
	{
		PrevPageSegment = CreateWidget<UMenuSegmentWidget>(this);
		
		if(!!PrevPageIcon)
			PrevPageSegment->IconTexture = PrevPageIcon;

		PrevPageSegment->IconColor = PageIconsColor;

		MenuSegments.Insert(PrevPageSegment, 0);
	}

	if (addNextPage == true)
	{
		NextPageSegment = CreateWidget<UMenuSegmentWidget>(this);

		if (!!NextPageIcon)
			NextPageSegment->IconTexture = NextPageIcon;

		NextPageSegment->IconColor = PageIconsColor;

		MenuSegments.Insert(NextPageSegment, MaxSegmentCount / 2);
	}

	for (int i = 0; i < MenuSegments.Num(); i++)
	{
		MenuSegments[i]->SetSegmentIndexAndCount(i, MenuSegments.Num());
		UCanvasPanelSlot* canvasPanelSlot = SegmentsCanvasPanel->AddChildToCanvas(MenuSegments[i]);
		canvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
		canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		canvasPanelSlot->SetAutoSize(true);
		MenuSegments[i]->SetRenderScale(FVector2D(0.75f, 0.75f));
	}

	return true;
}

void UBuildingMenuWidget::CorrectPageDetails(TArray<FDataTableRowHandle> InBuildingObjects, TArray<FDataTableRowHandle> OutBuildingObjects, bool OutAddNextPage, bool OutAddPrevPage)
{
	TArray<FDataTableRowHandle> buildingObjects = InBuildingObjects;
	TArray<FDataTableRowHandle> resultBuildingObjects;
	int32 lenghth = InBuildingObjects.Num();
	int32 startIndex = 0;
	bool addNextPage = false;
	bool addPrevPage = false;

	if (lenghth <= MaxSegmentCount)
	{
		Pages = 1;
		CurrentPage = 1;
		startIndex = 0;
		addNextPage = false;
		addPrevPage = false;
	}
	else if (lenghth <= (MaxSegmentCount - 1) * 2)
	{
		Pages = 2;
		CurrentPage = FMath::Clamp(CurrentPage, 1, 2);
		startIndex = (CurrentPage - 1) * (MaxSegmentCount - 1);
		addNextPage = (CurrentPage == 1) ? true : false;
		addPrevPage = (CurrentPage == 1) ? false : true;
	}
	else
	{
		Pages = 3;

		while (lenghth > ((MaxSegmentCount - 1) * 2) + ((Pages - 2) * (MaxSegmentCount - 2)))
		{
			Pages += 1;
		}
		CurrentPage = FMath::Clamp(CurrentPage, 1, Pages);
		startIndex = (CurrentPage > 1) ? ((MaxSegmentCount - 1) + ((CurrentPage - 2) * (MaxSegmentCount - 2))) : 0;
		addNextPage = (CurrentPage != Pages) ? true : false;
		addPrevPage = (CurrentPage != 1) ? true : false;
	}

	for (int i = 0; i < buildingObjects.Num(); i++)
	{
		int32 nextReturnValue = addNextPage ? 1 : 0;
		int32 prevReturnValue = addPrevPage ? 1 : 0;

		if (resultBuildingObjects.Num() < (MaxSegmentCount - (addNextPage + addPrevPage)))
		{
			if (i >= startIndex)
			{
				resultBuildingObjects.Add(buildingObjects[i]);
			}
		}
		else
			break;
	}

	OutBuildingObjects = resultBuildingObjects;
	OutAddNextPage = addNextPage;
	OutAddPrevPage = addPrevPage;
	return;
}
