// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "CarPlayerControler.h"
#include "MyWheeledVehiclePawn.h"
#include "FinalCheckpoint.h"

#include "SinglePlayerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMNA_API ASinglePlayerGameModeBase : public AGameMode
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AMyWheeledVehiclePawn> PawnSpawnClass;

	UPROPERTY(EditAnywhere)
	int LapCount = 1;

	UPROPERTY(EditAnywhere)
	float TimePerLap = 200.f;

public:

	void StartPlay();

	void EndMatch() override;
	
	UFUNCTION()
	int GetLapCount();

	UFUNCTION()
	void SetLapCount(int Laps);
	
	UFUNCTION()
	float GetTimePerLap();
	
	UFUNCTION()
	void SetTimePerLap(float Time);

};
