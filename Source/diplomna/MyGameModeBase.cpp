// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"



void AMyGameModeBase::StartPlay() {

    Super::StartPlay();
    UWorld* World = GetWorld();
    UGameUserSettings::GetGameUserSettings()->ApplySettings(true);
    UGameplayStatics::CreatePlayer(World, 0, true);
    APlayerController* Controller1 = UGameplayStatics::GetPlayerController(World, 0);
    AActor* Player1Start = FindPlayerStart(Controller1, "P1"); 
    AMyWheeledVehiclePawn* Player1 = World->SpawnActor<AMyWheeledVehiclePawn>(PawnSpawnClass, Player1Start->GetActorLocation(), Player1Start->GetActorRotation());
    UGameplayStatics::CreatePlayer(World, 1, true);
    APlayerController* Controller2 = UGameplayStatics::GetPlayerController(World, 1);
    AActor* Player2Start = FindPlayerStart(Controller2, "P2");
    AMyWheeledVehiclePawn* Player2 = World->SpawnActor<AMyWheeledVehiclePawn>(PawnSpawnClass, Player2Start->GetActorLocation(), Player2Start->GetActorRotation());

    Controller1->Possess(Player1);
    Controller2->Possess(Player2);

    AFinalCheckpoint* FinishLine = World->SpawnActor<AFinalCheckpoint>(FVector(Player1Start->GetActorLocation().X - 1500, Player1Start->GetActorLocation().Y - 500, Player1Start->GetActorLocation().Z), Player1Start->GetActorRotation());
    FinishLine->BoxComp->SetBoxExtent(FVector(32, 2000, 2000));

    OptionsString.RemoveAt(0, 1, true);
    SetLapCount(FCString::Atoi(*(OptionsString)));

    if (Player2->GetController() == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Player 2 not initialized"));
    }
    else 
    {
        Player2->SetWrongDirectionCheckpoint(FinishLine);
        Player2->SetMaxLaps(LapCount);
    }

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


int AMyGameModeBase::GetLapCount()
{
    return LapCount;
}

void AMyGameModeBase::SetLapCount(int Laps)
{
    LapCount = Laps;
}

void AMyGameModeBase::EndMatch()
{
    Super::EndMatch();
    StartToLeaveMap();
    FString Options = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
    Options.RemoveFromEnd(FString("1p"), ESearchCase::CaseSensitive);
    UE_LOG(LogTemp, Warning, TEXT("Gamemode map name: %s"), *Options);
    Options.Append(" ");
    AMyWheeledVehiclePawn* Player1 = Cast<AMyWheeledVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    AMyWheeledVehiclePawn* Player2 = Cast<AMyWheeledVehiclePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 1));
    if ((Player1->GetFastestTime() < Player2->GetFastestTime() && Player1->GetFastestTime() != -1.f) || (Player2->GetFastestTime() == -1.f))//if player 1 has done the fastest lap
    {
        Options.Append(FString::SanitizeFloat(Player1->GetFastestTime()));
        Options.Append(" ");
        Options.Append("1");
        Options.Append(" ");
    }
    else
    {
        Options.Append(FString::SanitizeFloat(Player2->GetFastestTime()));
        Options.Append(" ");
        Options.Append("2");
        Options.Append(" ");
    }
    if (Player1->HasWon)
    {
        Options.Append("1");
    }
    else
    {
        Options.Append("2");
    }
    UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(GetWorld(), 1), true);
    UGameplayStatics::OpenLevel(GetWorld(), FName("EndGameLevel"), true, Options);

}