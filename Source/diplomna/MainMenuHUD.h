// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HowToPlayWidget.h"
#include "LeaderboardWidget.h"
#include "PlayWidget.h"
#include "MainMenuWidget.h"
#include "EditorClassUtils.h"
#include "OptionsMenuWidget.h"

#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMNA_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
public:

	AMainMenuHUD();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMainMenuWidget* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHowToPlayWidget* HowToPlayWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HowToPlayWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULeaderboardWidget* LeaderboardWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> LeaderboardWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayWidget* PlayMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PlayMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UOptionsMenuWidget* OptionsMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OptionsMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Laps = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GameMode = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MapName = "circuit";

	UFUNCTION()
	void ChangeLaps(int LapCount);

	UFUNCTION()
	void PlayGame();

	UFUNCTION()
	void SelectMap(FString Map);

	UFUNCTION()
	void OpenPlayMenu(int GameModeNum);

	UFUNCTION()
	void OpenHowToPlayMenu();

	UFUNCTION()
	void OpenLeaderboardMenu();

	UFUNCTION()
	void OpenOptionsMenu();

	UFUNCTION()
	void CloseOptionsMenu();

	UFUNCTION()
	void ClosePlayMenu();

	UFUNCTION()
	void CloseHowToPlayMenu();

	UFUNCTION()
	void CloseLeaderboardMenu();


};
