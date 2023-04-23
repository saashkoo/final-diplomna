// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

APlayerHUD::APlayerHUD() 
{

}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass != nullptr )
	{
		Widget = CreateWidget<UTwoPlayerWidget>(GetWorld(), WidgetClass);
		Widget->SetOwner(GetOwningPlayerController()->GetLocalPlayer()->GetControllerId());
			Widget->AddToPlayerScreen();

		Widget->UpdateSelectedPowerup(0);
	}
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();
}

void APlayerHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerHUD::UpdateSpeed(int Speed)
{
	Widget->UpdateSpeed(Speed);
}


void APlayerHUD::UpdateLapTime(FString Time)
{
	Widget->UpdateLapTime( Time);
}

void APlayerHUD::UpdateHealthBar(int CurrentHP, int MaxHP)
{
	Widget->UpdateHealthBar(CurrentHP, MaxHP);
}

void APlayerHUD::UpdatePowerups(int PowerupSlot, int NewPowerup)
{
	Widget->UpdatePowerups(PowerupSlot,NewPowerup);
}


void APlayerHUD::UpdateSelectedPowerup(int PowerupSlot)
{
	Widget->UpdateSelectedPowerup(PowerupSlot);
}

void APlayerHUD::UpdateLaps(int CurrLap, int MaxHP)
{
	Widget->UpdateLaps(CurrLap, MaxHP);
}