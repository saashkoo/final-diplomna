// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TwoPlayerWidget.h"
#include "Components/WidgetComponent.h"

#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DIPLOMNA_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	APlayerHUD();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTwoPlayerWidget* Widget;

	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void UpdateSpeed(int Speed);

	UFUNCTION()
	void UpdateLapTime(FString Time);

	UFUNCTION()
	void UpdateHealthBar(int CurrentHP, int MaxHP);

	UFUNCTION()
	void UpdatePowerups(int PowerupSlot, int NewPowerup);

	UFUNCTION()
	void UpdateSelectedPowerup(int PowerupSlot);

	UFUNCTION()
	void UpdateLaps(int CurrLap, int MaxLaps);


};
