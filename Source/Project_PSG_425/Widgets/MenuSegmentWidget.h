#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSegmentWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSelectedSignature, UMenuSegmentWidget*, InMenuSegmentWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickedSignature, UMenuSegmentWidget*, InMenuSegmentWidget);

UCLASS()
class PROJECT_PSG_425_API UMenuSegmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	virtual	bool UpdateWidget();
	
	bool CheckSelection(float CurrentRotation);
	bool ClearSelection();

	void TryClick();
	void SetSegmentIndexAndCount(int32 NewSegmentIndex, int32 NewSegmentCount);

	bool SetSelection(bool InSelected);

public:
	UPROPERTY(BlueprintAssignable)
		FSelectedSignature OnSelected;

	UPROPERTY(BlueprintAssignable)
		FClickedSignature OnClicked;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
		int32 SegmentIndex = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		int32 SegmentCount = 16;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor IconColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor BackgroundColor = FLinearColor(0.05f, 0.05f, 0.05f, 0.5f);

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor SelectedColor = FLinearColor(1.f, 0.5f, 0.f, 1.f);

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor DefaultColor = FLinearColor(0.35f, 0.3f, 0.3f, 1.f);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		class UTexture2D* IconTexture;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
		TArray<class UTexture2D*> SegmentImageTextures;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		TArray<class UTexture2D*> SegmentFrameTextures;

	float Rotation = 0.f;
	float SegmentAngle = 0.f;

	bool IsSelected;
	bool UpdateIconColor = true;

public:
	UPROPERTY(meta = (BindWidget))
		class UImage* SegmentBackground;

	UPROPERTY(meta = (BindWidget))
		class UImage* SegmentFrame;

	UPROPERTY(meta = (BindWidget))
		class UImage* SegmentIcon;

	UPROPERTY(meta = (BindWidget))
		class UOverlay* SegmentOverlay;
};
