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

    OptionsString.RemoveAt(0, 1, true);
    SetLapCount(FCString::Atoi(*(OptionsString)));

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
    StartToLeaveMap();
    FString Options = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
    Options.RemoveFromEnd(FString("1p"), ESearchCase::CaseSensitive);
    UE_LOG(LogTemp, Warning, TEXT("Gamemode map name: %s"), *Options);
    Options.Append(" ");
    AMyWheeledVehiclePawn* Player1 = Cast<AMyWheeledVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    Options.Append(FString::SanitizeFloat(Player1->GetFastestTime()));
    Options.Append(" ");
    Options.Append("1");
    Options.Append(" ");
    Options.Append("1");
    UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(GetWorld(), 1), true);
    UGameplayStatics::OpenLevel(GetWorld(), FName("EndGameLevel"), true, Options);
    //a
}