#include "MenuSegmentWidget.h"
#include "Global.h"
#include "Components/Image.h"
#include "Components/Overlay.h"

void UMenuSegmentWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateWidget();
	ClearSelection();
}

void UMenuSegmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateWidget();
	ClearSelection();
}

bool UMenuSegmentWidget::UpdateWidget()
{
	SegmentCount = FMath::Clamp(SegmentCount, 1, 16);
	SegmentAngle = 360.f / (float)SegmentCount;

	float value = (float)SegmentIndex * SegmentAngle;
	Rotation = value > 180.f ? value - 360 : value;

	//Image Texture Brush Settings
	if(!!SegmentImageTextures[SegmentCount - 1])
		if(!!SegmentBackground)
			SegmentBackground->SetBrushFromTexture(SegmentImageTextures[SegmentCount - 1]);

	if(!!SegmentFrameTextures[SegmentCount - 1])
		if(!!SegmentFrame)
			SegmentFrame->SetBrushFromTexture(SegmentFrameTextures[SegmentCount - 1]);

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
	// 스크린의 마우스위치와 위젯의 회전에 따라서 위젯선택
	float returnValue;

	returnValue = CurrentRotation > 0 && Rotation == 180 ? CurrentRotation - 360.f : CurrentRotation;

	if ((Rotation * -1) + (SegmentAngle / 2) > returnValue && (Rotation * -1) - (SegmentAngle / 2) < returnValue)
	{
		if (IsSelected == false)
		{
			SetSelection(true);
			return true;
		}
	}
	else
	{
		if (IsSelected == true)
		{
			ClearSelection();
		}
			return false;
	}

	return false;
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
	if (GetIsEnabled() && IsSelected)
	{
		if (OnClicked.IsBound())
			OnClicked.Broadcast(this);
	}
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

		if (OnSelected.IsBound())
			OnSelected.Broadcast(this);

		return true;
	}
	else
	{
		return ClearSelection();
	}
}
