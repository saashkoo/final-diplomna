// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "FastestTimeSaveGame.h"


#include "LeaderboardWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(SingleCastNoParamsDelegate);

UCLASS()
class DIPLOMNA_API ULeaderboardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	SingleCastNoParamsDelegate ReturnToMainMenuDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* Leaderboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PrevButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* NextButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> MapSavesNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentMapIndex = 0;

	UFUNCTION()
	void BackButtonPressed();

	UFUNCTION()
	void PrevButtonPressed();

	UFUNCTION()
	void NextButtonPressed();

	UFUNCTION()
	void LoadSaveGame();
};
