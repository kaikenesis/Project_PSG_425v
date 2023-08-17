#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBuilding.generated.h"

UINTERFACE(MinimalAPI)
class UIBuilding : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_PSG_425_API IIBuilding
{
	GENERATED_BODY()

public:
	virtual void CheckSpawn();
	virtual void Spawn();
};
