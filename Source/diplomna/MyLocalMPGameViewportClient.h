// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Engine.h"
#include "UnrealClient.h"

#include "MyLocalMPGameViewportClient.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMNA_API UMyLocalMPGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
    virtual bool InputAxis(FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad) override;
	virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;
};
