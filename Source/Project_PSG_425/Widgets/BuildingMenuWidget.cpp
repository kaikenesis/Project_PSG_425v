#include "BuildingMenuWidget.h"
#include "Global.h"
#include "DataTable/CustomDataTables.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "BuildingMenuSegmentWidget.h"
#include "MenuSegmentWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UBuildingMenuWidget::UBuildingMenuWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	CHelpers::GetClass(&BuildingMenuSegmentClass, "/Game/Widgets/WB_BuildingMenuSegment");
	CHelpers::GetClass(&MenuSegmentClass, "/Game/Widgets/WB_MenuSegment");
}

void UBuildingMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	ConstructWidget();
}

void UBuildingMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BtnClick->OnClicked.AddDynamic(this, &UBuildingMenuWidget::OnClicked);

	ConstructWidget();
}

void UBuildingMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UpdateMouseRotation();
	
	for (int i = 0; i < MenuSegments.Num(); i++)
		MenuSegments[i]->CheckSelection(Rotation);
}

bool UBuildingMenuWidget::ConstructWidget()
{
	CurrentBuildingList = DefaultBuildingList;
	CurrentBuildingDataTable = DefaultBuildingDataTable;

	return UpdateWidget();

}

bool UBuildingMenuWidget::UpdateWidget()
{
	MaxSegmentCount = FMath::Clamp(MaxSegmentCount, 3, 16);

	bool result;

	if (!!CurrentBuildingList.DataTable)
		result = CurrentBuildingList.RowName != FName("None");
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

	TArray<FDataTableRowHandle> resultBuildingObjects;
	CorrectPageDetails(BuildingObjects, resultBuildingObjects);

	for (int i = 0; i < resultBuildingObjects.Num(); i++)
	{
		UBuildingMenuSegmentWidget* buildingMenuSegment = CreateWidget<UBuildingMenuSegmentWidget>(this, BuildingMenuSegmentClass);

		buildingMenuSegment->BuildingObjectHandle = resultBuildingObjects[i];
		buildingMenuSegment->SegmentIndex = i;
		buildingMenuSegment->SegmentCount = 16;
		
		MenuSegments.Add(buildingMenuSegment);
	}
	
	if (AddPrevPage == true)
	{
		PrevPageSegment = CreateWidget<UMenuSegmentWidget>(this, MenuSegmentClass);
		
		if(!!PrevPageIcon)
			PrevPageSegment->IconTexture = PrevPageIcon;

		PrevPageSegment->IconColor = PageIconsColor;

		MenuSegments.Insert(PrevPageSegment, 0);
		PrevPageSegment->OnClicked.AddDynamic(this, &UBuildingMenuWidget::PrevPageClicked);
	}

	if (AddNextPage == true)
	{
		NextPageSegment = CreateWidget<UMenuSegmentWidget>(this, MenuSegmentClass);

		if (!!NextPageIcon)
			NextPageSegment->IconTexture = NextPageIcon;

		NextPageSegment->IconColor = PageIconsColor;

		MenuSegments.Insert(NextPageSegment, MaxSegmentCount / 2);
		NextPageSegment->OnClicked.AddDynamic(this, &UBuildingMenuWidget::NextPageClicked);
	}

	for (int i = 0; i < MenuSegments.Num(); i++)
	{
		MenuSegments[i]->SetSegmentIndexAndCount(i, MenuSegments.Num());
		UCanvasPanelSlot* canvasPanelSlot = SegmentsCanvasPanel->AddChildToCanvas(MenuSegments[i]);
		canvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
		canvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		canvasPanelSlot->SetAutoSize(true);

		MenuSegments[i]->SetRenderScale(FVector2D(0.75f, 0.75f));
		MenuSegments[i]->OnSelected.AddDynamic(this, &UBuildingMenuWidget::SegmentSelected);
		MenuSegments[i]->OnClicked.AddDynamic(this, &UBuildingMenuWidget::SegmentClicked);
	}

	return true;
}

void UBuildingMenuWidget::CorrectPageDetails(TArray<FDataTableRowHandle> InBuildingObjects, TArray<FDataTableRowHandle> &OutBuildingObjects)
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
	AddNextPage = addNextPage;
	AddPrevPage = addPrevPage;
	return;
}

void UBuildingMenuWidget::UpdateMouseRotation()
{
	FVector2D viewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
	FVector viewportVector = UKismetMathLibrary::MakeVector(viewportSize.X / 2, viewportSize.Y / 2, 0.f);

	float locationX;
	float locationY;
	GetOwningPlayer()->GetMousePosition(locationX, locationY);
	FVector mousePosition = UKismetMathLibrary::MakeVector(locationX, locationY, 0.f);

	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(viewportVector, mousePosition);
	Rotation = rotation.Yaw > 0.f ? rotation.Yaw - 180.f : rotation.Yaw + 180.f;

	FVector distanceVector = viewportVector - mousePosition;
	Distance = distanceVector.Size();
}

void UBuildingMenuWidget::OnClicked()
{
	for (int i = 0; i < MenuSegments.Num(); i++)
		MenuSegments[i]->TryClick();
}

void UBuildingMenuWidget::SegmentSelected(class UMenuSegmentWidget* InMenuSegmentWidget)
{
	UBuildingMenuSegmentWidget* buildingMenuSegment = Cast<UBuildingMenuSegmentWidget>(InMenuSegmentWidget);

	if (!!buildingMenuSegment)
	{
		if (OnBuildingSegmentSelected.IsBound())
			OnBuildingSegmentSelected.Broadcast(buildingMenuSegment);
	}
	else
	{
		if (OnMenuSegmentSelected.IsBound())
			OnMenuSegmentSelected.Broadcast(InMenuSegmentWidget);
	}
}

void UBuildingMenuWidget::SegmentClicked(class UMenuSegmentWidget* InMenuSegmentWidget)
{
	UBuildingMenuSegmentWidget* buildingMenuSegment = Cast<UBuildingMenuSegmentWidget>(InMenuSegmentWidget);

	if (!!buildingMenuSegment)
	{
		if (OnBuildingSegmentClicked.IsBound())
			OnBuildingSegmentClicked.Broadcast(buildingMenuSegment);
	}
	else
	{
		if (OnMenuSegmentClicked.IsBound())
			OnMenuSegmentClicked.Broadcast(InMenuSegmentWidget);
	}
}

void UBuildingMenuWidget::PrevPageClicked(UMenuSegmentWidget* InMenuSegmentWidget)
{
	CurrentPage = FMath::Clamp(CurrentPage - 1, 1, Pages);
	UpdateSegments();
}

void UBuildingMenuWidget::NextPageClicked(UMenuSegmentWidget* InMenuSegmentWidget)
{
	CurrentPage = FMath::Clamp(CurrentPage + 1, 1, Pages);
	UpdateSegments();
}
