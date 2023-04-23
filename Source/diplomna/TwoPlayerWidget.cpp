// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoPlayerWidget.h"

void UTwoPlayerWidget::UpdateSpeed(int InSpeed)
{
	if(this)
	{
		Speed->SetText(FText::FromString(FString::FromInt(InSpeed) + "kph"));
	}
	
}

void UTwoPlayerWidget::UpdateLapTime(FString InTime)
{
	if (this)
	{
		LapTime->SetText(FText::FromString(InTime));
	}
	
}

void UTwoPlayerWidget::UpdateLaps(int CurrLap, int MaxLaps)
{
	if (this)
	{
		Laps->SetText(FText::FromString(FString::FromInt(CurrLap) + "/" + FString::FromInt(MaxLaps)));
	}
}

void UTwoPlayerWidget::UpdateHealthBar(int CurrentHP, int MaxHP)
{
	if (this)
	{
		HealthBar->SetPercent(float(CurrentHP) / float(MaxHP));
	}
	
}

void UTwoPlayerWidget::UpdatePowerups(int PowerupSlot, int NewPowerup)
{
	if (this)
	{
		if (PowerupSlot == 0) {
			PowerupSlot1->SetBrushFromTexture(PowerupIcons[NewPowerup], false);
		}
		if (PowerupSlot == 1) {
			PowerupSlot2->SetBrushFromTexture(PowerupIcons[NewPowerup], false);
		}
		if (PowerupSlot == 2) {
			PowerupSlot3->SetBrushFromTexture(PowerupIcons[NewPowerup], false);
		}
	}
}

void UTwoPlayerWidget::UpdateSelectedPowerup(int PowerupSlot)
{
	if (this)
	{
		if (PowerupSlot == 0)
		{
			PowerupSelectSlot1->SetVisibility(ESlateVisibility::Visible);
			PowerupSelectSlot2->SetVisibility(ESlateVisibility::Hidden);
			PowerupSelectSlot3->SetVisibility(ESlateVisibility::Hidden);
		}
		if (PowerupSlot == 1)
		{
			PowerupSelectSlot2->SetVisibility(ESlateVisibility::Visible);
			PowerupSelectSlot1->SetVisibility(ESlateVisibility::Hidden);
			PowerupSelectSlot3->SetVisibility(ESlateVisibility::Hidden);
		}
		if (PowerupSlot == 2)
		{
			PowerupSelectSlot3->SetVisibility(ESlateVisibility::Visible);
			PowerupSelectSlot2->SetVisibility(ESlateVisibility::Hidden);
			PowerupSelectSlot1->SetVisibility(ESlateVisibility::Hidden);
		}

	}
	
}

void UTwoPlayerWidget::SetOwner(const int32 ControllerId)
{
	if (!GetWorld()) 
	{
		return;
	}
	ULocalPlayer* InPlayer = GEngine->GetLocalPlayerFromControllerId(GetWorld(), ControllerId);
	Super::SetPlayerContext(InPlayer);
};
