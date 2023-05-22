// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidget.h"

void UPlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BackButton->OnClicked.AddDynamic(this, &UPlayWidget::BackButtonPressed);
	CircuitButton->OnClicked.AddDynamic(this, &UPlayWidget::CircuitButtonPressed);
	CanyonButton->OnClicked.AddDynamic(this, &UPlayWidget::CanyonButtonPressed);
	DecreaseLapsButton->OnClicked.AddDynamic(this, &UPlayWidget::DecreaseLapsButtonPressed);
	IncreaseLapsButton->OnClicked.AddDynamic(this, &UPlayWidget::IncreaseLapsButtonPressed);
}

void	UPlayWidget::BackButtonPressed()
{
	ReturnToMainMenuDelegate.ExecuteIfBound();
}

void	UPlayWidget::CircuitButtonPressed()
{
	MapNameDelegate.ExecuteIfBound(MapNames[0]);
}

void	UPlayWidget::CanyonButtonPressed()
{
	MapNameDelegate.ExecuteIfBound(MapNames[1]);
}

void	UPlayWidget::DecreaseLapsButtonPressed()
{
	int LapCount = FCString::Atoi(*(Laps->GetText().ToString()));
	if (LapCount > 1)
	{
		LapCount--;
		Laps->SetText(FText::AsNumber(LapCount));
		LapCountDelegate.ExecuteIfBound(LapCount);
	}
}

void	UPlayWidget::IncreaseLapsButtonPressed()
{
	int LapCount = FCString::Atoi(*(Laps->GetText().ToString()));
	LapCount++;
	Laps->SetText(FText::AsNumber(LapCount));
	LapCountDelegate.ExecuteIfBound(LapCount);
}