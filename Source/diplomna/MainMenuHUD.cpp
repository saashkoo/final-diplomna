// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"

AMainMenuHUD::AMainMenuHUD()
{
	
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	GetOwningPlayerController()->bShowMouseCursor = true;
	GetOwningPlayerController()->bEnableClickEvents = true;
	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidget->SelectedGameModeDelegate.BindUObject(this, &AMainMenuHUD::OpenPlayMenu);
	MainMenuWidget->OpenHowToPlayMenuDelegate.BindUObject(this, &AMainMenuHUD::OpenHowToPlayMenu);
	MainMenuWidget->OpenLeaderboardMenuDelegate.BindUObject(this, &AMainMenuHUD::OpenLeaderboardMenu);
	MainMenuWidget->OpenOptionsMenuDelegate.BindUObject(this, &AMainMenuHUD::OpenOptionsMenu);

	HowToPlayWidget = CreateWidget<UHowToPlayWidget>(GetWorld(), HowToPlayWidgetClass);
	HowToPlayWidget->ReturnToMainMenuDelegate.BindUObject(this, &AMainMenuHUD::CloseHowToPlayMenu);
	HowToPlayWidget->NextButtonPressed();

	LeaderboardWidget = CreateWidget<ULeaderboardWidget>(GetWorld(), LeaderboardWidgetClass);
	LeaderboardWidget->ReturnToMainMenuDelegate.BindUObject(this, &AMainMenuHUD::CloseLeaderboardMenu);
	LeaderboardWidget->NextButtonPressed();

	PlayMenuWidget = CreateWidget<UPlayWidget>(GetWorld(), PlayMenuWidgetClass);
	PlayMenuWidget->LapCountDelegate.BindUObject(this, &AMainMenuHUD::ChangeLaps);
	PlayMenuWidget->MapNameDelegate.BindUObject(this, &AMainMenuHUD::SelectMap);
	PlayMenuWidget->ReturnToMainMenuDelegate.BindUObject(this, &AMainMenuHUD::ClosePlayMenu);

	OptionsMenuWidget = CreateWidget<UOptionsMenuWidget>(GetWorld(), OptionsMenuWidgetClass);
	OptionsMenuWidget->ReturnToMainMenuDelegate.BindUObject(this, &AMainMenuHUD::CloseOptionsMenu);
	

	MainMenuWidget->AddToViewport();
	HowToPlayWidget->AddToViewport();
	LeaderboardWidget->AddToViewport();
	PlayMenuWidget->AddToViewport();
	OptionsMenuWidget->AddToViewport();

	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	HowToPlayWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	LeaderboardWidget->SetVisibility(ESlateVisibility::Hidden);
	OptionsMenuWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMainMenuHUD::ChangeLaps(int LapCount)
{
	Laps = LapCount;
}

void AMainMenuHUD::PlayGame()
{
	FString Options = FString::FromInt(Laps);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(Options));
	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName), true, Options);
}

void AMainMenuHUD::SelectMap(FString Map)
{
	MapName = Map;
	if (Map == PlayMenuWidget->MapNames[1])
	{
		ChangeLaps(1);
	}
	if (GameMode == 1)
	{
		MapName.Append("1p");
	}
	PlayGame();
}

void AMainMenuHUD::OpenPlayMenu(int GameModeNum)
{
	GameMode = GameModeNum;
	MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void  AMainMenuHUD::OpenHowToPlayMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	HowToPlayWidget->SetVisibility(ESlateVisibility::Visible);
}

void  AMainMenuHUD::OpenLeaderboardMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	LeaderboardWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainMenuHUD::OpenOptionsMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	OptionsMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainMenuHUD::ClosePlayMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	PlayMenuWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMainMenuHUD::CloseHowToPlayMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	HowToPlayWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMainMenuHUD::CloseLeaderboardMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	LeaderboardWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AMainMenuHUD::CloseOptionsMenu()
{
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	OptionsMenuWidget->SetVisibility(ESlateVisibility::Hidden);
}