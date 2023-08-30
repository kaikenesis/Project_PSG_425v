#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBuildingWidget.generated.h"

UINTERFACE(MinimalAPI)
class UIBuildingWidget : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_PSG_425_API IIBuildingWidget
{
	GENERATED_BODY()

public:
	virtual void ShowBuildingMenu_Interface() = 0;
	virtual void HideBuildingMenu_Interface() = 0;
};
