// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWheeledVehiclePawn.h"


AMyWheeledVehiclePawn::AMyWheeledVehiclePawn() 
{
    MaxLaps = 0;
    CurrentLap = 1;
    ResetCheckpoint = nullptr;
    WrongDirectionCheckpoint = nullptr;
    camera_cycle = 0;
    ResetLocation = FVector(0.0f, 0.0f, 0.0f);
    ResetRotation = FRotator(0.0f, 0.0f, 0.0f);
    GetVehicleMovementComponent()->SetUseAutomaticGears(true);
    
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 300.0f;
    OurCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
    OurCameraComponent->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);


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
        OurCameraComponent->SetRelativeLocation(FVector(200.0f, 0.0f, 100.0f));
        OurCameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    }
    if (camera_cycle == 1) {
        OurCameraComponent->SetRelativeLocation(FVector(-450.0f, 0.0f, 350.0f));
        OurCameraComponent->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
    }
    camera_cycle = camera_cycle + 1;

    if (camera_cycle == max_cameras) {
        camera_cycle = 0;
    }
}

int AMyWheeledVehiclePawn::GetCamCycle()
{
    return camera_cycle;
}

void AMyWheeledVehiclePawn::SetCamCycle(int cycle)
{
    while (cycle > max_cameras) {
        cycle = cycle - max_cameras;
    }

    while (cycle < 0) {
        cycle = cycle + max_cameras;
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
    ResetLocation.Y = ResetLocation.Y + spawn_offset;
    ResetLocation = ResetLocation + Offset;
    bTeleportSucceeded = MyWorld->FindTeleportSpot(this, ResetLocation, ResetRotation);
    ResetLocation = ResetLocation - Offset;
    if (bTeleportSucceeded)
    {
        this->GetMovementComponent()->Deactivate();
        this->TeleportTo(ResetLocation, ResetRotation);
        this->GetMovementComponent()->Activate();
        ResetLocation.Y = ResetLocation.Y - spawn_offset;
        UE_LOG(LogTemp, Error, TEXT("end2 y = %f"), ResetLocation.Y);
        return;
    }
    else 
    {
        ResetLocation.Y = ResetLocation.Y - spawn_offset;
    }

}

AActor* AMyWheeledVehiclePawn::GetResetCheckpoint()
{
    return ResetCheckpoint;
}

AActor* AMyWheeledVehiclePawn::GetWrongDirectionCheckpoint()
{
    return WrongDirectionCheckpoint;
}

void AMyWheeledVehiclePawn::SetResetCheckpoint(AActor* NewCheckpoint)
{
    if (NewCheckpoint != nullptr)
    {
        if (ResetCheckpoint != nullptr) //if player has passed a checkpoint
        {
            WrongDirectionCheckpoint = ResetCheckpoint;
        }
        ResetCheckpoint = NewCheckpoint;
        ResetLocation = ResetCheckpoint->GetActorLocation();
        ResetRotation = ResetCheckpoint->GetActorRotation();
    }
    
}

void AMyWheeledVehiclePawn::SetWrongDirectionCheckpoint(AActor* NewCheckpoint)
{
    if (WrongDirectionCheckpoint == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("ok ,for now"));
    }
    if (NewCheckpoint != nullptr)
    {
        WrongDirectionCheckpoint = NewCheckpoint;
    }
    if (WrongDirectionCheckpoint == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("oof"));
    }


}

void AMyWheeledVehiclePawn::SetMaxLaps(unsigned int LapCount)
{
    MaxLaps = LapCount;
}

void AMyWheeledVehiclePawn::SetCurrentLap(unsigned int LapCount)
{
    CurrentLap = LapCount;
}

void AMyWheeledVehiclePawn::CompleteLap()
{
    if (CurrentLap == MaxLaps) 
    {
        UE_LOG(LogTemp, Error, TEXT("Finished race"));
    }
    CurrentLap++;
}

unsigned int AMyWheeledVehiclePawn::GetMaxLaps()
{
    return MaxLaps;
}

unsigned int AMyWheeledVehiclePawn::GetCurrentLap()
{
    return CurrentLap;
}
