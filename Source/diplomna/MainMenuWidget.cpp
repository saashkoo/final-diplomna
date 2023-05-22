// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TwoPlayerButton->OnClicked.AddDynamic(this, &UMainMenuWidget::TwoPlayerButtonPressed);
	OnePlayerButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnePlayerButtonPressed);
	LeaderboardButton->OnClicked.AddDynamic(this, &UMainMenuWidget::LeaderboardButtonPressed);
	HowToPlayButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HowToPlayButtonPressed);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitButtonPressed);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OptionsButtonPressed);
}

void UMainMenuWidget::TwoPlayerButtonPressed()
{
	SelectedGameModeDelegate.ExecuteIfBound(0);
}

void UMainMenuWidget::OnePlayerButtonPressed()
{
	SelectedGameModeDelegate.ExecuteIfBound(1);
}

void UMainMenuWidget::LeaderboardButtonPressed() 
{
	OpenLeaderboardMenuDelegate.ExecuteIfBound();
}

void UMainMenuWidget::HowToPlayButtonPressed()
{
	OpenHowToPlayMenuDelegate.ExecuteIfBound();
}

void UMainMenuWidget::QuitButtonPressed()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

void UMainMenuWidget::OptionsButtonPressed()
{
	OpenOptionsMenuDelegate.ExecuteIfBound();
}