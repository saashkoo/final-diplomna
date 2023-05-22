// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Array.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Components/Image.h"

#include "PlayerWidget.generated.h"


/**
 * 
 */
UCLASS()
class DIPLOMNA_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
public:


	void UpdateSpeed(int Speed);

	void UpdateLapTime(FString Time);

	void UpdateLaps(int CurrLap, int MaxLaps);

	void UpdateHealthBar(int CurrentHP, int MaxHP);

	void UpdatePowerups(int PowerupSlot, int NewPowerup);

	void UpdateSelectedPowerup(int PowerupSlot);

	UFUNCTION(BlueprintCallable, Category = UserInterface)
	void SetOwner(const int32 ControllerId);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* LapTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* Laps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* PowerupSlot1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* PowerupSlot2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* PowerupSlot3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* PowerupSelectSlot1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* PowerupSelectSlot2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* PowerupSelectSlot3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UTexture2D*> PowerupIcons;
};