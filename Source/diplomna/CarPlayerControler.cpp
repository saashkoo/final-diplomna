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
        InputComponent->BindAction("UsePowerup", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::UseSelectedPowerup);
        InputComponent->BindAction("ChangeSlot", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::NextPowerupSlot);
        InputComponent->BindAction("PowerupDrop", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::DropPowerup);
        
    }
    if (GetLocalPlayer()->GetControllerId() == 1)
    {
        //UE_LOG(LogTemp, Error, TEXT("it works?"));
        InputComponent->BindAxis("P2_Steering", Instanced, &AMyWheeledVehiclePawn::Steer);
        InputComponent->BindAxis("P2_Throttle", Instanced, &AMyWheeledVehiclePawn::Accelerate);
        InputComponent->BindAction("P2_ChangeCam", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::ChangeCam);
        InputComponent->BindAction("P2_Reset", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::Reset);
        InputComponent->BindAction("P2_UsePowerup", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::UseSelectedPowerup);
        InputComponent->BindAction("P2_ChangeSlot", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::NextPowerupSlot);
        InputComponent->BindAction("P2_PowerupDrop", IE_Pressed, Instanced, &AMyWheeledVehiclePawn::DropPowerup);
    }

}