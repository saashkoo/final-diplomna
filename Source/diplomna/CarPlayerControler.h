// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyWheeledVehiclePawn.h"

#include "CarPlayerControler.generated.h"


/**
 * 
 */
UCLASS()
class DIPLOMNA_API ACarPlayerControler : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void OnPossess(APawn* InPawn) override;
};
