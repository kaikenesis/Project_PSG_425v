#include "PatrolPath.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"

APatrolPath::APatrolPath()
{
	CHelpers::CreateSceneComponent(this, &Root, "Root");
	CHelpers::CreateSceneComponent(this, &Spline, "Spline", Root);
	CHelpers::CreateSceneComponent(this, &Text, "Text", Root);

	Spline->SetRelativeLocation(FVector(0.f, 0.f, 30.f));

	Text->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	Text->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	Text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Text->SetTextRenderColor(FColor::Red);

	Spline->bShouldVisualizeScale = true;
	Spline->ScaleVisualizationWidth = 20;
}

void APatrolPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Spline->SetClosedLoop(bClosedLoop);
	Text->K2_SetText(FText::FromString(GetActorLabel()));
}

void APatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
	Text->SetVisibility(false);
}

