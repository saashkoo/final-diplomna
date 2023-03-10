// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLocalMPGameViewportClient.h"



bool UMyLocalMPGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
    UEngine* const Engine = GetOuterUEngine();
    int32 const NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
    bool bRetVal = false;
    for (int32 i = 0; i < NumPlayers; i++)
    {
        FInputKeyEventArgs arg = FInputKeyEventArgs(EventArgs.Viewport, i, EventArgs.Key, EventArgs.Event, EventArgs.AmountDepressed, EventArgs.bIsTouchEvent);
        bRetVal = Super::InputKey(arg);
        bRetVal;
    }

    return bRetVal;
}

bool UMyLocalMPGameViewportClient::InputAxis(FViewport* InputViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
    {
        UEngine* const Engine = GetOuterUEngine();
        int32 const NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
        bool bRetVal = false;
        for (int32 i = 0; i < NumPlayers; i++)
        {
            bRetVal = Super::InputAxis(InputViewport, i, Key, Delta, DeltaTime, NumSamples, bGamepad);
            bRetVal;
        }

        return bRetVal;
    }
}