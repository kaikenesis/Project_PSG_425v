#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "BuildingMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingSegmentClickedSignature, class UBuildingMenuSegmentWidget*, InBuildingMenuSegmentWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingSegmentSelectedSignature, class UBuildingMenuSegmentWidget*, InBuildingMenuSegmentWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuSegmentClickedSignature, class UMenuSegmentWidget*, InMenuSegmentWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuSegmentSelectedSignature, class UMenuSegmentWidget*, InMenuSegmentWidget);

UCLASS()
class PROJECT_PSG_425_API UBuildingMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBuildingMenuWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
		bool ConstructWidget();

public:
	bool UpdateWidget();
	bool UpdateBuildingList(FDataTableRowHandle InBuildingListHandle);
	bool UpdateBuildingDataTable(UDataTable* InDataTable);
	bool UpdateSegments();
	void CorrectPageDetails(TArray<FDataTableRowHandle> InBuildingObjects, TArray<FDataTableRowHandle> &OutBuildingObjects);
	void UpdateMouseRotation();

public: // Delegate에 의해 호출될 함수
	UFUNCTION()
		void SegmentSelected(class UMenuSegmentWidget* InMenuSegmentWidget);

	UFUNCTION()
		void SegmentClicked(class UMenuSegmentWidget* InMenuSegmentWidget);

	UFUNCTION()
		void PrevPageClicked(class UMenuSegmentWidget* InMenuSegmentWidget);

	UFUNCTION()
		void NextPageClicked(class UMenuSegmentWidget* InMenuSegmentWidget);

	UFUNCTION()
		void OnClicked();

public:
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* SegmentsCanvasPanel;

	UPROPERTY(meta = (BindWidget))
		class UButton* BtnClick;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		FDataTableRowHandle DefaultBuildingList;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		UDataTable* DefaultBuildingDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		int32 MaxSegmentCount = 6;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		int32 Pages = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		int32 CurrentPage = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		FLinearColor PageIconsColor = FLinearColor(0.255208f, 0.255208f, 0.255208f, 1.f);

public:
	FBuildingSegmentClickedSignature OnBuildingSegmentClicked;
	FBuildingSegmentSelectedSignature OnBuildingSegmentSelected;
	FMenuSegmentClickedSignature OnMenuSegmentClicked;
	FMenuSegmentSelectedSignature OnMenuSegmentSelected;

private:
	UPROPERTY(EditDefaultsOnly)
		FDataTableRowHandle CurrentBuildingList;

	UDataTable* CurrentBuildingDataTable;
	class UMenuSegmentWidget* PrevPageSegment;
	class UMenuSegmentWidget* NextPageSegment;

	TArray<FDataTableRowHandle> BuildingObjects;
	TArray<class UMenuSegmentWidget*> MenuSegments;
	
	TSubclassOf<class UBuildingMenuSegmentWidget> BuildingMenuSegmentClass;
	TSubclassOf<class UMenuSegmentWidget> MenuSegmentClass;

	UPROPERTY(EditDefaultsOnly)
		UTexture2D* PrevPageIcon;

	UPROPERTY(EditDefaultsOnly)
		UTexture2D* NextPageIcon;

	bool AddNextPage = false;
	bool AddPrevPage = false;

	float Rotation;
	float Distance;

};
