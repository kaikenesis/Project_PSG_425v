#pragma once

#include "CoreMinimal.h"
#include "Widgets/MenuSegmentWidget.h"
#include "Engine/DataTable.h"
#include "BuildingMenuSegmentWidget.generated.h"

UCLASS()
class PROJECT_PSG_425_API UBuildingMenuSegmentWidget : public UMenuSegmentWidget
{
	GENERATED_BODY()

public:
	virtual bool UpdateWidget() override;

public:
	FDataTableRowHandle BuildingObjectHandle;
};
