// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Containers/Array.h"

#include "HowToPlayWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(SingleCastNoParamsDelegate);

UCLASS()
class DIPLOMNA_API UHowToPlayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	SingleCastNoParamsDelegate ReturnToMainMenuDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* HelpImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* NextButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PrevButton;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<UTexture2D*> HelpSlides;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int HelpSlidesIndex = 0;

	UFUNCTION()
	void NextButtonPressed();

	UFUNCTION()
	void PrevButtonPressed();

	UFUNCTION()
	void BackButtonPressed();
};
