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
	virtual void NativeConstruct() override;
	virtual bool Initialize() override; // UserWidget¿« BeginPlay

public:
	UFUNCTION()
		virtual bool UpdateWidget();
	
	UFUNCTION()
		bool CheckSelection(float CurrentRotation);
	
	UFUNCTION()
		bool ClearSelection();

	UFUNCTION()
		void TryClick();

	UFUNCTION()
		void SetSegmentIndexAndCount(int32 NewSegmentIndex, int32 NewSegmentCount);

	UFUNCTION()
		bool SetSelection(bool InSelected);

public:
	UPROPERTY(BlueprintAssignable)
		FSelectedSignature OnSelected;

	UPROPERTY(BlueprintAssignable)
		FClickedSignature OnClicked;

protected:
	int32 SegmentIndex = 0;
	int32 SegmentCount = 16;

	float Rotation = 0.f;
	float SegmentAngle = 0.f;

	bool IsSelected;
	bool UpdateIconColor = true;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Color")
		FLinearColor IconColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	UPROPERTY(EditDefaultsOnly, Category = "Color")
		FLinearColor BackgroundColor = FLinearColor(0.05f, 0.05f, 0.05f, 0.5f);

	UPROPERTY(EditDefaultsOnly, Category = "Color")
		FLinearColor SelectedColor = FLinearColor(1.f, 0.5f, 0.f, 1.f);

	UPROPERTY(EditDefaultsOnly, Category = "Color")
		FLinearColor DefaultColor = FLinearColor(0.35f, 0.3f, 0.3f, 1.f);

	UPROPERTY(EditDefaultsOnly, Category = "Texture")
		class UTexture2D* IconTexture;

	UPROPERTY(EditDefaultsOnly, Category = "Texture")
		TArray<class UTexture2D*> SegmentImageTextures;

	UPROPERTY(EditDefaultsOnly, Category = "Texture")
		TArray<class UTexture2D*> SegmentFrameTextures;

protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* SegmentBackground;

	UPROPERTY(meta = (BindWidget))
		class UImage* SegmentFrame;

	UPROPERTY(meta = (BindWidget))
		class UImage* SegmentIcon;

	UPROPERTY(meta = (BindWidget))
		class UOverlay* SegmentOverlay;
};
