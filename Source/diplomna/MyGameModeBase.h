// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "FastestTimeSaveGame.h"
#include "CarPlayerControler.h"
#include "MyWheeledVehiclePawn.h"
#include "FinalCheckpoint.h"

#include "MyGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class DIPLOMNA_API AMyGameModeBase : public AGameMode
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AMyWheeledVehiclePawn> PawnSpawnClass;

	UPROPERTY(EditAnywhere)
	int LapCount = 1;


	

public:
	void StartPlay();

	void EndMatch() override;

	UFUNCTION()
	int GetLapCount();

	UFUNCTION()
	void SetLapCount(int Laps);

};
