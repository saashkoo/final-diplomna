// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePlayerGameModeBase.h"

void ASinglePlayerGameModeBase::StartPlay() {

    Super::StartPlay();
    UWorld* World = GetWorld();
    UGameplayStatics::CreatePlayer(World, 0, true);
    APlayerController* Controller1 = UGameplayStatics::GetPlayerController(World, 0);
    AActor* Player1Start = FindPlayerStart(Controller1, "P1");
    AMyWheeledVehiclePawn* Player1 = World->SpawnActor<AMyWheeledVehiclePawn>(PawnSpawnClass, Player1Start->GetActorLocation(), Player1Start->GetActorRotation());
    

    Controller1->Possess(Player1);

    AFinalCheckpoint* FinishLine = World->SpawnActor<AFinalCheckpoint>(FVector(Player1Start->GetActorLocation().X - 1500, Player1Start->GetActorLocation().Y - 500, Player1Start->GetActorLocation().Z), Player1Start->GetActorRotation());
    FinishLine->BoxComp->SetBoxExtent(FVector(32, 2000, 2000));

    if (Player1->GetController() == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Player 1 not initialized"));
    }
    else
    {
        Player1->SetWrongDirectionCheckpoint(FinishLine);
        Player1->SetMaxLaps(LapCount);
    }

    FAsyncLoadGameFromSlotDelegate LoadedDelegate;
    LoadedDelegate.BindUObject(Player1, &AMyWheeledVehiclePawn::LoadGameDelegateFunction);
    UGameplayStatics::AsyncLoadGameFromSlot("defalut", 0, LoadedDelegate);
}


int ASinglePlayerGameModeBase::GetLapCount()
{
    return LapCount;
}

void ASinglePlayerGameModeBase::SetLapCount(int Laps)
{
    LapCount = Laps;
}

float ASinglePlayerGameModeBase::GetTimePerLap()
{
    return TimePerLap;
}

void ASinglePlayerGameModeBase::SetTimePerLap(float Time)
{
    TimePerLap = Time;
}

void ASinglePlayerGameModeBase::EndMatch()
{
    Super::EndMatch();
    if (UGameplayStatics::GetPlayerController(GetWorld(), 1)->GetGameTimeSinceCreation() < GetTimePerLap()) 
    {
        UE_LOG(LogTemp, Error, TEXT("You Won!"));
    }
    else 
    {
        UE_LOG(LogTemp, Error, TEXT("You Lost!"));
    }
    StartToLeaveMap();
    for (int i = 0; i < GetNumPlayers(); i++)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), i), EQuitPreference::Quit, false);
    }
    //a
}