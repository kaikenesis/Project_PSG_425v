#include "HealthWidget.h"
#include "Components/ProgressBar.h"

void UHealthWidget::UpdateHealth_Implementation(float InCurrentHealth, float InMaxHealth)
{
	HealthBar->SetPercent(InCurrentHealth / InMaxHealth);
}
