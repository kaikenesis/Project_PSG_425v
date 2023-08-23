#include "MenuSegmentWidget.h"
#include "Global.h"
#include "Components/Image.h"
#include "Components/Overlay.h"

void UMenuSegmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateWidget();
	ClearSelection();
}

bool UMenuSegmentWidget::Initialize()
{
	Super::Initialize();

	return true;
}

bool UMenuSegmentWidget::UpdateWidget()
{
	SegmentCount = UKismetMathLibrary::Clamp(SegmentCount, 1, 16);
	SegmentAngle = 360.f / (float)SegmentCount;

	float value = (float)SegmentIndex * SegmentAngle;
	Rotation = value > 180.f ? value - 360 : value;

	//Image Texture Brush Settings
	UTexture2D* imageTexture = SegmentImageTextures[SegmentCount - 1];
	if(!!imageTexture)
		if(!!SegmentBackground)
			SegmentBackground->SetBrushFromTexture(imageTexture);

	UTexture2D* frameTexture = SegmentFrameTextures[SegmentCount - 1];
	if(!!frameTexture)
		if(!!SegmentFrame)
			SegmentFrame->SetBrushFromTexture(imageTexture);

	if(!!IconTexture)
		if(!!SegmentIcon)
			SegmentIcon->SetBrushFromTexture(IconTexture);

	//Image Color Settings
	SegmentBackground->SetColorAndOpacity(BackgroundColor);
	SegmentIcon->SetColorAndOpacity(IconColor);

	SegmentIcon->SetRenderTransformAngle(Rotation);
	SegmentOverlay->SetRenderTransformAngle(Rotation * -1);

	return true;
}

bool UMenuSegmentWidget::CheckSelection(float CurrentRotation)
{
	return true;
}

bool UMenuSegmentWidget::ClearSelection()
{
	IsSelected = false;

	SegmentFrame->SetColorAndOpacity(DefaultColor);

	FLinearColor color = UpdateIconColor ? DefaultColor : FLinearColor(1.f, 1.f, 1.f);
	SegmentIcon->SetColorAndOpacity(color);

	return false;
}

void UMenuSegmentWidget::TryClick()
{
	//if(GetIsEnabled()&&IsSelected)
		//TODO: OnClicked Delegate 호출
}

void UMenuSegmentWidget::SetSegmentIndexAndCount(int32 NewSegmentIndex, int32 NewSegmentCount)
{
	SegmentIndex = NewSegmentIndex;
	SegmentCount = NewSegmentCount;

	UpdateWidget();
	ClearSelection();
}

bool UMenuSegmentWidget::SetSelection(bool InSelected)
{
	IsSelected = InSelected;

	if (IsSelected == true)
	{
		SegmentFrame->SetColorAndOpacity(SelectedColor);

		FLinearColor color = UpdateIconColor ? SelectedColor : FLinearColor(1.f, 1.f, 1.f);
		SegmentIcon->SetColorAndOpacity(color);

		//TODO: OnSelected Delegate 호출

		return true;
	}
	else
	{
		return ClearSelection();
	}

	return true;
}
