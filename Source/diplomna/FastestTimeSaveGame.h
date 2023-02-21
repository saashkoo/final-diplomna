// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Containers/Array.h" 
#include "Containers/Map.h"

#include "FastestTimeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMNA_API UFastestTimeSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
	UFastestTimeSaveGame();

	UPROPERTY(EditDefaultsOnly)
	TMap<float, FString> Times;
};
