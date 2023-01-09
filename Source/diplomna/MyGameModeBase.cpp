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

    if (Player2->GetController() == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Player 2 not initialized"));
    }

    if (Player1->GetController() == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Player 2 not initialized"));
    }
}
