// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/Button.h"

#include "PlayWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(IntDelegate, int);
DECLARE_DELEGATE_OneParam(FStringDelegate, FString);
DECLARE_DELEGATE(SingleCastNoParamsDelegate);

UCLASS()
class DIPLOMNA_API UPlayWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	FStringDelegate MapNameDelegate;

	IntDelegate LapCountDelegate;

	SingleCastNoParamsDelegate ReturnToMainMenuDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CircuitButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CanyonButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* DecreaseLapsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* IncreaseLapsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Laps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> MapNames;

	UFUNCTION()
	void	BackButtonPressed();

	UFUNCTION()
	void	CircuitButtonPressed();

	UFUNCTION()
	void	CanyonButtonPressed();

	UFUNCTION()
	void	DecreaseLapsButtonPressed();

	UFUNCTION()
	void	IncreaseLapsButtonPressed();

	
};
