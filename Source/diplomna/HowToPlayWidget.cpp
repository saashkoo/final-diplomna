// Fill out your copyright notice in the Description page of Project Settings.


#include "HowToPlayWidget.h"

void UHowToPlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &UHowToPlayWidget::BackButtonPressed);
	NextButton->OnClicked.AddDynamic(this, &UHowToPlayWidget::NextButtonPressed);
	PrevButton->OnClicked.AddDynamic(this, &UHowToPlayWidget::PrevButtonPressed);
}

void	UHowToPlayWidget::BackButtonPressed()
{
	ReturnToMainMenuDelegate.ExecuteIfBound();
}

void UHowToPlayWidget::NextButtonPressed()
{
	if (HelpSlidesIndex >= HelpSlides.Num() - 1)
	{
		HelpSlidesIndex = 0;
	}
	else
	{
		HelpSlidesIndex++;
	}
	HelpImage->SetBrushFromTexture(HelpSlides[HelpSlidesIndex], false);
}


void UHowToPlayWidget::PrevButtonPressed()
{
	if (HelpSlidesIndex > 0)
	{
		HelpSlidesIndex--;
	}
	else
	{
		HelpSlidesIndex = HelpSlides.Num() - 1;
	}
	HelpImage->SetBrushFromTexture(HelpSlides[HelpSlidesIndex], false);
}