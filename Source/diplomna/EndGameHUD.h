// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EndGameWidget.h"
#include "Misc/Timespan.h"
#include "FastestTimeSaveGame.h"
#include "Kismet/KismetSystemLibrary.h"

#include "EndGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMNA_API AEndGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AEndGameHUD();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEndGameWidget* EndGameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> EndGameWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimespan FastestTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WinningPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int FastestLapPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MapName;

	UFUNCTION()
	void ReturnToMainMenu();

	UFUNCTION()
	void ProcessString(FString InString);

	UFUNCTION()
	void QuitGame();

	UFUNCTION()
	void SaveFastestTime();

};
