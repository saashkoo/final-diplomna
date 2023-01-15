// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "CarPlayerControler.h"
#include "MyWheeledVehiclePawn.h"
#include "FinalCheckpoint.h"

#include "MyGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class DIPLOMNA_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, Category = "GameStart")
	TSubclassOf<AMyWheeledVehiclePawn> PawnSpawnClass;

	UPROPERTY(EditAnywhere)
	int LapCount = 2;


	

public:
	void StartPlay();

	int GetLapCount();

	void SetLapCount(int Laps);

};
