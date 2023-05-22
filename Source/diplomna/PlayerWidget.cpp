// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"

void UPlayerWidget::UpdateSpeed(int InSpeed)
{
	if(this)
	{
		Speed->SetText(FText::FromString(FString::FromInt(InSpeed) + "kph"));
	}
	
}

void UPlayerWidget::UpdateLapTime(FString InTime)
{
	if (this)
	{
		LapTime->SetText(FText::FromString(InTime));
	}
	
}

void UPlayerWidget::UpdateLaps(int CurrLap, int MaxLaps)
{
	if (this)
	{
		Laps->SetText(FText::FromString(FString::FromInt(CurrLap) + "/" + FString::FromInt(MaxLaps)));
	}
}

void UPlayerWidget::UpdateHealthBar(int CurrentHP, int MaxHP)
{
	if (this)
	{
		HealthBar->SetPercent(float(CurrentHP) / float(MaxHP));
	}
	
}

void UPlayerWidget::UpdatePowerups(int PowerupSlot, int NewPowerup)
{
	if (this)
	{
		switch (PowerupSlot)
		{
		case 0:
			PowerupSlot1->SetBrushFromTexture(PowerupIcons[NewPowerup], false);
			break;
		case 1:
			PowerupSlot2->SetBrushFromTexture(PowerupIcons[NewPowerup], false);
			break;
		case 2:
			PowerupSlot3->SetBrushFromTexture(PowerupIcons[NewPowerup], false);
			break;
		}
	}
}

void UPlayerWidget::UpdateSelectedPowerup(int PowerupSlot)
{
	if (this)
	{
		switch (PowerupSlot)
		{
		case 0:
			PowerupSelectSlot1->SetVisibility(ESlateVisibility::Visible);
			PowerupSelectSlot2->SetVisibility(ESlateVisibility::Hidden);
			PowerupSelectSlot3->SetVisibility(ESlateVisibility::Hidden);
			break;
		case 1:
			PowerupSelectSlot2->SetVisibility(ESlateVisibility::Visible);
			PowerupSelectSlot1->SetVisibility(ESlateVisibility::Hidden);
			PowerupSelectSlot3->SetVisibility(ESlateVisibility::Hidden);
			break;
		case 2:
			PowerupSelectSlot3->SetVisibility(ESlateVisibility::Visible);
			PowerupSelectSlot2->SetVisibility(ESlateVisibility::Hidden);
			PowerupSelectSlot1->SetVisibility(ESlateVisibility::Hidden);
			break;
		}
	}	
}

void UPlayerWidget::SetOwner(const int32 ControllerId)
{
	if (!GetWorld()) 
	{
		return;
	}
	ULocalPlayer* InPlayer = GEngine->GetLocalPlayerFromControllerId(GetWorld(), ControllerId);
	Super::SetPlayerContext(InPlayer);
};
