// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"
#include "Types/SlateEnums.h"

#include "OptionsMenuWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(SingleCastNoParamsDelegate);

UCLASS()
class DIPLOMNA_API UOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	SingleCastNoParamsDelegate ReturnToMainMenuDelegate;

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameUserSettings* Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UFUNCTION()
	void BackButtonPressed();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* ResolutionComboBoxString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* OverallQualitySlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* AntiAliasingQualitySlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* FoliageQualitySlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* PostProcessingQualitySlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* TextureQualitySlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* ShadowQualitySlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* ShadingQualitySlider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USlider* GlobalIlluminationQualitySlider;

	UFUNCTION()
	void ResolutionComboBoxStringChanged(FString NewString, ESelectInfo::Type NewSelectInfo);

	UFUNCTION()
	void OverallQualitySliderChanged(float NewValue);

	UFUNCTION()
	void AntiAliasingQualitySliderChanged(float NewValue);

	UFUNCTION()
	void FoliageQualitySliderChanged(float NewValue);

	UFUNCTION()
	void PostProcessingQualitySliderChanged(float NewValue);

	UFUNCTION()
	void TextureQualitySliderChanged(float NewValue);

	UFUNCTION()
	void ShadowQualitySliderChanged(float NewValue);

	UFUNCTION()
	void ShadingQualitySliderChanged(float NewValue);

	UFUNCTION()
	void GlobalIlluminationQualitySliderChanged(float NewValue);
};
