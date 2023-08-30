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
	void PreConstruct(bool IsDesignTime);
	void Construct();

	void Tick(FGeometry MyGeometry, float InDeltaTime);

public:
	void ConstructWidget(bool Success = false);
	void UpdateWidget(bool Success = false);
	void UpdateBuildingList(FDataTableRowHandle InBuildingListHandle, bool Success = false);
	void UpdateBuildingDataTable(UDataTable* InDataTable, bool Success = false);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		FDataTableRowHandle DefaultBuildingList;
	FDataTableRowHandle CurrentBuildingList;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		UDataTable* DefaultBuildingDataTable;
	UDataTable* CurrentBuildingDataTable;

	TArray<FDataTableRowHandle> BuildingObjects;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		int32 MaxSegmentCount = 6;
};
