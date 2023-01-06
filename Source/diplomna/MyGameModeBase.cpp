// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"



void AMyGameModeBase::StartPlay() {

    Super::StartPlay();

    UWorld* World = GetWorld();
    UGameplayStatics::CreatePlayer(World, 0, true);
    APlayerController* Controller1 = UGameplayStatics::GetPlayerController(World, 0);
    AMyWheeledVehiclePawn* Player1 = World->SpawnActor<AMyWheeledVehiclePawn>(PawnSpawnClass, FVector(-24778.322974f, 6622.661215f, 19320.184375f), FRotator(0, 0, 0));
    UGameplayStatics::CreatePlayer(World, 1, true);
    APlayerController* Controller2 = UGameplayStatics::GetPlayerController(World, 1);
    AMyWheeledVehiclePawn* Player2 = World->SpawnActor<AMyWheeledVehiclePawn>(PawnSpawnClass, FVector(-24778.322974f, 6900.661215f, 19320.184375f), FRotator(0, 0, 0));

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
