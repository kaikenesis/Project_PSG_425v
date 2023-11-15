#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Melee.generated.h"

UCLASS()
class PROJECT_PSG_425_API UBTService_Melee : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_Melee();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
