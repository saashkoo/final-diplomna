// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameWidget.h"

void UEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	QuitGameButton->OnClicked.AddDynamic(this, &UEndGameWidget::QuitGameButtonPressed);
	ReturnToMainMenuButton->OnClicked.AddDynamic(this, &UEndGameWidget::ReturnToMainMenuButtonPressed);
	ConfirmButton->OnClicked.AddDynamic(this, &UEndGameWidget::ConfirmButtonPressed);
}

void UEndGameWidget::QuitGameButtonPressed()
{
	QuitGameDelegate.ExecuteIfBound();
}

void UEndGameWidget::ReturnToMainMenuButtonPressed()
{
	ReturnToMainMenuDelegate.ExecuteIfBound();
}

void UEndGameWidget::ConfirmButtonPressed()
{
	ConfirmNameDelegate.ExecuteIfBound();
}