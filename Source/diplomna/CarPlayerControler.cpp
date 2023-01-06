// Fill out your copyright notice in the Description page of Project Settings.


#include "CarPlayerControler.h"

void ACarPlayerControler::OnPossess(APawn* InPawn)
{

    Super::OnPossess(InPawn);
    AMyWheeledVehiclePawn* Instanced = Cast<AMyWheeledVehiclePawn>(InPawn);
    if (IsValid(Instanced) == false) {
        UE_LOG(LogTemp, Error, TEXT("Wrong Pawn"));
        return;
    }
    if (GetLocalPlayer()->GetControllerId() == 0) 
    {
        InputComponent->BindAxis("MySteering", Instanced, &AMyWheeledVehiclePawn::Steer);
        InputComponent->BindAxis("MyThrottle", Instanced, &AMyWheeledVehiclePawn::Accelerate);
        InputComponent->BindAction("ChangeCam", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::ChangeCam);
        InputComponent->BindAction("Reset", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::Reset);
    }
    if (GetLocalPlayer()->GetControllerId() == 1)
    {
        UE_LOG(LogTemp, Error, TEXT("it works?"));
        InputComponent->BindAxis("P2_Steering", Instanced, &AMyWheeledVehiclePawn::Steer);
        InputComponent->BindAxis("P2_Throttle", Instanced, &AMyWheeledVehiclePawn::Accelerate);
        InputComponent->BindAction("P2_ChangeCam", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::ChangeCam);
        InputComponent->BindAction("P2_Reset", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::Reset);
    }

}