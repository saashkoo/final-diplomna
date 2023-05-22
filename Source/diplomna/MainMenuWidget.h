// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(IntDelegate, int);
DECLARE_DELEGATE(SingleCastNoParamsDelegate);

UCLASS()
class DIPLOMNA_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	IntDelegate SelectedGameModeDelegate;

	SingleCastNoParamsDelegate OpenLeaderboardMenuDelegate;

	SingleCastNoParamsDelegate OpenHowToPlayMenuDelegate;

	SingleCastNoParamsDelegate OpenOptionsMenuDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TwoPlayerButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton * OnePlayerButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton * LeaderboardButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton * HowToPlayButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton * QuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OptionsButton;

	UFUNCTION()
	void OptionsButtonPressed();

	UFUNCTION()
	void TwoPlayerButtonPressed();

	UFUNCTION()
	void OnePlayerButtonPressed();

	UFUNCTION()
	void LeaderboardButtonPressed();

	UFUNCTION()
	void HowToPlayButtonPressed();

	UFUNCTION()
	void QuitButtonPressed();

};
