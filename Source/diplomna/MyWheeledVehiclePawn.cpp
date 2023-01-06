// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWheeledVehiclePawn.h"


AMyWheeledVehiclePawn::AMyWheeledVehiclePawn() 
{
    camera_cycle = 0;
    ResetLocation = FVector(0.0f, 0.0f, 0.0f);
    ResetRotation = FRotator(0.0f, 0.0f, 0.0f);
    GetVehicleMovementComponent()->SetUseAutomaticGears(true);//ne pravi nishto
    
    PrimaryActorTick.bCanEverTick = true;

    OurCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
    OurCameraComponent->SetupAttachment(RootComponent);
    OurCameraComponent->SetRelativeLocation(FVector(-450.0f, 0.0f, 350.0f));
    OurCameraComponent->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

}

void AMyWheeledVehiclePawn::BeginPlay()
{
    Super::BeginPlay();
    ResetLocation = GetActorLocation();
}

void AMyWheeledVehiclePawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AMyWheeledVehiclePawn::Accelerate(float AxisValue)
{
    if (AxisValue >= 0) {
        GetVehicleMovementComponent()->SetThrottleInput(AxisValue);
        GetVehicleMovementComponent()->SetBrakeInput(0);
    }
    if (AxisValue < 0) {
        AxisValue = AxisValue * -1;
        GetVehicleMovementComponent()->SetBrakeInput(AxisValue);
        GetVehicleMovementComponent()->SetThrottleInput(0);
    }
}
void AMyWheeledVehiclePawn::Steer(float AxisValue)
{
    GetVehicleMovementComponent()->SetSteeringInput(AxisValue);
}

void AMyWheeledVehiclePawn::ChangeCam()
{
    UE_LOG(LogTemp, Error, TEXT("gear: %d"), GetVehicleMovementComponent()->GetCurrentGear());
    UE_LOG(LogTemp, Error, TEXT("speed: %f"), GetVehicleMovementComponent()->GetForwardSpeedMPH());
    UE_LOG(LogTemp, Error, TEXT("usesautogear: %d"), GetVehicleMovementComponent()->GetUseAutoGears());

    if (camera_cycle == 0) {
        OurCameraComponent->SetRelativeLocation(FVector(200.0f, 0.0f, 200.0f));
        OurCameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    }
    if (camera_cycle == 1) {
        OurCameraComponent->SetRelativeLocation(FVector(-450.0f, 0.0f, 350.0f));
        OurCameraComponent->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
    }
    camera_cycle = camera_cycle + 1;

    if (camera_cycle == 2) {
        camera_cycle = 0;
    }
}

int AMyWheeledVehiclePawn::GetCamCycle()
{
    return camera_cycle;
}

void AMyWheeledVehiclePawn::SetCamCycle(int cycle)
{
    while (cycle > 2) {
        cycle = cycle - 2;
    }

    while (cycle < 0) {
        cycle = cycle + 2;
    }
    camera_cycle = cycle;
}

void AMyWheeledVehiclePawn::SetResetLocation(FVector NewLocation, FRotator NewRotation)
{
    ResetLocation = NewLocation;
    ResetRotation = NewRotation;
}

void AMyWheeledVehiclePawn::Reset()
{
    UE_LOG(LogTemp, Error, TEXT("start y = %f"), ResetLocation.Y);
    UWorld* MyWorld = GetWorld();
    FVector Offset = GetRootComponent()->Bounds.Origin - GetActorLocation();
    ResetLocation = ResetLocation + Offset;
    bool bTeleportSucceeded = MyWorld->FindTeleportSpot(this, ResetLocation, ResetRotation);
    ResetLocation = ResetLocation - Offset;
    if (bTeleportSucceeded)
    {
        this->GetMovementComponent()->Deactivate();
        this->TeleportTo(ResetLocation, ResetRotation);
        this->GetMovementComponent()->Activate();
        UE_LOG(LogTemp, Error, TEXT("end1 y = %f"), ResetLocation.Y);
        return;
    }

    //attempts to find a new spawn
    ResetLocation.Y = ResetLocation.Y + 500;
    ResetLocation = ResetLocation + Offset;
    bTeleportSucceeded = MyWorld->FindTeleportSpot(this, ResetLocation, ResetRotation);
    ResetLocation = ResetLocation - Offset;
    if (bTeleportSucceeded)
    {
        this->GetMovementComponent()->Deactivate();
        this->TeleportTo(ResetLocation, ResetRotation);
        this->GetMovementComponent()->Activate();
        ResetLocation.Y = ResetLocation.Y - 500;
        UE_LOG(LogTemp, Error, TEXT("end2 y = %f"), ResetLocation.Y);
        return;
    }
}