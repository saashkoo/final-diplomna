// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Components/EditableTextBox.h"

#include "EndGameWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(SingleCastNoParamsDelegate);

UCLASS()
class DIPLOMNA_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	SingleCastNoParamsDelegate ReturnToMainMenuDelegate;

	SingleCastNoParamsDelegate QuitGameDelegate;

	SingleCastNoParamsDelegate ConfirmNameDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ReturnToMainMenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* PlayerNameEditableTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* WinningPlayerTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FastestLapTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ConfirmButton;

	UFUNCTION()
	void QuitGameButtonPressed();

	UFUNCTION()
	void ReturnToMainMenuButtonPressed();

	UFUNCTION()
	void ConfirmButtonPressed();
};
