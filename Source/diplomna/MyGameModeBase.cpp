// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"



void AMyGameModeBase::StartPlay() {

    Super::StartPlay();
    UWorld* World = GetWorld();
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
        UE_LOG(LogTemp, Error, TEXT("Player 2 not initialized"));
    }
    else
    {
        Player1->SetWrongDirectionCheckpoint(FinishLine);
        Player1->SetMaxLaps(LapCount);
    }
}


int AMyGameModeBase::GetLapCount()
{
    return LapCount;
}

void AMyGameModeBase::SetLapCount(int Laps)
{
    LapCount = Laps;
}
