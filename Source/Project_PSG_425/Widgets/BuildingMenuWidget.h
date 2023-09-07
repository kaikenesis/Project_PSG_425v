#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "BuildingMenuWidget.generated.h"

UCLASS()
class PROJECT_PSG_425_API UBuildingMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	bool ConstructWidget();
	bool UpdateWidget();
	bool UpdateBuildingList(FDataTableRowHandle InBuildingListHandle);
	bool UpdateBuildingDataTable(UDataTable* InDataTable);
	bool UpdateSegments();
	void CorrectPageDetails(TArray<FDataTableRowHandle> InBuildingObjects, TArray<FDataTableRowHandle> OutBuildingObjects, bool OutAddNextPage = false, bool OutAddPrevPage = false);

public:
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* SegmentsCanvasPanel;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		FDataTableRowHandle DefaultBuildingList;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		UDataTable* DefaultBuildingDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		int32 MaxSegmentCount = 6;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		int32 Pages = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		int32 CurrentPage = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		FLinearColor PageIconsColor = FLinearColor(0.255208f, 0.255208f, 0.255208f, 1.f);

private:
	UPROPERTY(EditDefaultsOnly)
		FDataTableRowHandle CurrentBuildingList;

	UDataTable* CurrentBuildingDataTable;
	class UMenuSegmentWidget* PrevPageSegment;
	class UMenuSegmentWidget* NextPageSegment;

	TArray<FDataTableRowHandle> BuildingObjects;
	TArray<class UMenuSegmentWidget*> MenuSegments;
	
	TSubclassOf<class UMenuSegmentWidget*> BuildingMenuSegmentClass;

	UPROPERTY(EditDefaultsOnly)
		UTexture2D* PrevPageIcon;

	UPROPERTY(EditDefaultsOnly)
		UTexture2D* NextPageIcon;

};
