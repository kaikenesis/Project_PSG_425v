#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Magic.generated.h"

UCLASS()
class PROJECT_PSG_425_API UBTService_Magic : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_Magic();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
