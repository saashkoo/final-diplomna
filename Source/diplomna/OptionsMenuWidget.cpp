// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsMenuWidget.h"

void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Settings = UGameUserSettings::GetGameUserSettings();
	Settings->LoadSettings();
	BackButton->OnClicked.AddDynamic(this, &UOptionsMenuWidget::BackButtonPressed);
	ResolutionComboBoxString->OnSelectionChanged.AddDynamic(this, &UOptionsMenuWidget::ResolutionComboBoxStringChanged);
	OverallQualitySlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::OverallQualitySliderChanged);
	AntiAliasingQualitySlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::AntiAliasingQualitySliderChanged);
	FoliageQualitySlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::FoliageQualitySliderChanged);
	PostProcessingQualitySlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::PostProcessingQualitySliderChanged);
	TextureQualitySlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::TextureQualitySliderChanged);
	ShadowQualitySlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::ShadowQualitySliderChanged);
	ShadingQualitySlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::ShadingQualitySliderChanged);
	GlobalIlluminationQualitySlider->OnValueChanged.AddDynamic(this, &UOptionsMenuWidget::GlobalIlluminationQualitySliderChanged);
}

void UOptionsMenuWidget::BackButtonPressed()
{
	Settings->SaveSettings();
	Settings->ApplySettings(false);
	ReturnToMainMenuDelegate.ExecuteIfBound();
}

void UOptionsMenuWidget::ResolutionComboBoxStringChanged(FString NewString, ESelectInfo::Type NewSelectInfo)
{
	FString X;
	FString Y;
	NewString.Split(FString("X"), &X, &Y);
	Settings->SetScreenResolution(FIntPoint(FCString::Atoi(*X), FCString::Atoi(*Y)));
	UE_LOG(LogTemp, Warning, TEXT("changed resolution to %d, %d"), FCString::Atoi(*X), FCString::Atoi(*Y));
}

void UOptionsMenuWidget::OverallQualitySliderChanged(float NewValue)
{
	
	int NewQuality = (int)NewValue;
	UE_LOG(LogTemp, Warning, TEXT("changed OverallQuality to %d"), NewQuality);
	Settings->SetOverallScalabilityLevel(NewQuality);
	OverallQualitySlider->SetValue(NewQuality);
	AntiAliasingQualitySlider->SetValue((float)Settings->GetAntiAliasingQuality());
	FoliageQualitySlider->SetValue((float)Settings->GetFoliageQuality());
	PostProcessingQualitySlider->SetValue((float)Settings->GetPostProcessingQuality());
	TextureQualitySlider->SetValue((float)Settings->GetTextureQuality());
	ShadowQualitySlider->SetValue((float)Settings->GetShadowQuality());
	ShadingQualitySlider->SetValue((float)Settings->GetShadingQuality());
	GlobalIlluminationQualitySlider->SetValue((float)Settings->GetGlobalIlluminationQuality());
}

void UOptionsMenuWidget::AntiAliasingQualitySliderChanged(float NewValue)
{
	
	int NewQuality = (int)NewValue;
	UE_LOG(LogTemp, Warning, TEXT("changed AntiAliasingQuality to %d"), NewQuality);
	Settings->SetAntiAliasingQuality(NewQuality);
	AntiAliasingQualitySlider->SetValue(NewQuality);
}

void UOptionsMenuWidget::FoliageQualitySliderChanged(float NewValue)
{
	
	int NewQuality = (int)NewValue;
	UE_LOG(LogTemp, Warning, TEXT("changed FoliageQualityto %d"), NewQuality);
	Settings->SetFoliageQuality(NewQuality);
	FoliageQualitySlider->SetValue(NewQuality);
}

void UOptionsMenuWidget::PostProcessingQualitySliderChanged(float NewValue)
{
	
	int NewQuality = (int)NewValue;
	UE_LOG(LogTemp, Warning, TEXT("changed PostProcessingQualityto %d"), NewQuality);
	Settings->SetPostProcessingQuality(NewQuality);
	PostProcessingQualitySlider->SetValue(NewQuality);
}

void UOptionsMenuWidget::TextureQualitySliderChanged(float NewValue)
{
	
	int NewQuality = (int)NewValue;
	UE_LOG(LogTemp, Warning, TEXT("changed TextureQualityto %d"), NewQuality);
	Settings->SetTextureQuality(NewQuality);
	TextureQualitySlider->SetValue(NewQuality);
}

void UOptionsMenuWidget::ShadowQualitySliderChanged(float NewValue)
{
	
	int NewQuality = (int)NewValue;
	UE_LOG(LogTemp, Warning, TEXT("changed ShadowQualityto %d"), NewQuality);
	Settings->SetShadowQuality(NewQuality);
	ShadowQualitySlider->SetValue(NewQuality);
}

void UOptionsMenuWidget::ShadingQualitySliderChanged(float NewValue)
{
	
	int NewQuality = (int)NewValue;
	UE_LOG(LogTemp, Warning, TEXT("changed ShadingQualityto %d"), NewQuality);
	Settings->SetShadingQuality(NewQuality);
	ShadingQualitySlider->SetValue(NewQuality);
}

void UOptionsMenuWidget::GlobalIlluminationQualitySliderChanged(float NewValue)
{
	
	int NewQuality = (int)NewValue;
	UE_LOG(LogTemp, Warning, TEXT("changed GlobalIlluminationQualityto %d"), NewQuality);
	Settings->SetGlobalIlluminationQuality(NewQuality);
	GlobalIlluminationQualitySlider->SetValue(NewQuality);
}