#include "NameWidget.h"
#include "Components/TextBlock.h"

void UNameWidget::SetNames_Implementation(const FString& InControllerName, const FString& InPawnName)
{
	ControllerName->SetText(FText::FromString(InControllerName));
	PawnName->SetText(FText::FromString(InPawnName));
}
