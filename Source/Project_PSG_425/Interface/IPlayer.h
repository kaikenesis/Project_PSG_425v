#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Engine/DataTable.h"
#include "IPlayer.generated.h"

UINTERFACE(MinimalAPI)
class UIPlayer : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_PSG_425_API IIPlayer
{
	GENERATED_BODY()

public:
	virtual void TryStartBuildObject_Interface(FDataTableRowHandle InBuildingObjectHandle) = 0;
};
