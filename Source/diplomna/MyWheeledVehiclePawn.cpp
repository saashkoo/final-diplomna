// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWheeledVehiclePawn.h"


AMyWheeledVehiclePawn::AMyWheeledVehiclePawn(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomVehicleMovementComponent>(VehicleMovementComponentName))
{
    Powerups[0] = PowerupsEnum::NONE;
    Powerups[1] = PowerupsEnum::NONE;
    Powerups[2] = PowerupsEnum::NONE;
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
    this->GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AMyWheeledVehiclePawn::OnOverlap);
}


void AMyWheeledVehiclePawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if(Hp <= 0)
    {
        this->Reset();
    }
    
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
        Hp = MaxHp;
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
        Hp = MaxHp;
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

void AMyWheeledVehiclePawn::SetPowerup(PowerupsEnum Value, int Slot)
{
    Powerups[Slot] = Value;
}

PowerupsEnum AMyWheeledVehiclePawn::GetPowerup(int Slot)
{
    return Powerups[Slot];
}

void AMyWheeledVehiclePawn::SetHp(int Value)
{
    while (Value > MaxHp) {
        Value = Value - MaxHp;
    }

    while (Value < 0) {
        Value = Value + MaxHp;
    }
    Hp = Value;
}

int AMyWheeledVehiclePawn::GetHp()
{
    return Hp;
}

void AMyWheeledVehiclePawn::UseSelectedPowerup()
{
    if (Powerups[PowerupSlot] == PowerupsEnum::NONE)
    {
        return;
    }
    if (Powerups[PowerupSlot] == PowerupsEnum::HEAL)
    {
        UseHeal();
        Powerups[PowerupSlot] = PowerupsEnum::NONE;
        return;
    }
    if (Powerups[PowerupSlot] == PowerupsEnum::SHIELD)
    {
        UseShield();
        Powerups[PowerupSlot] = PowerupsEnum::NONE;
        return;
    }
    if (Powerups[PowerupSlot] == PowerupsEnum::BOOST)
    {
        UseBoost();
        Powerups[PowerupSlot] = PowerupsEnum::NONE;
        return;
    }
    if (Powerups[PowerupSlot] == PowerupsEnum::PROJECTILE)
    {
        UseProjectile();
        Powerups[PowerupSlot] = PowerupsEnum::NONE;
        return;
    }
}

void AMyWheeledVehiclePawn::SetPowerupSlot(int Value)
{
    while (Value >= MaxPowerupSlots) {
        Value = Value - MaxPowerupSlots;
    }

    while (Value < 0) {
        Value = Value + MaxPowerupSlots;
    }
    PowerupSlot = Value;
}

int AMyWheeledVehiclePawn::GetPowerupSlot()
{
    return PowerupSlot;
}

void AMyWheeledVehiclePawn::SetShield(int Value) 
{
    if (Value < 0)
    {
        Value = Value * -1;
    }
    Shield = Value;
    UE_LOG(LogTemp, Warning, TEXT("Shield: %d"), this->GetShield());
}

int AMyWheeledVehiclePawn::GetShield()
{
    return Shield;
}

void AMyWheeledVehiclePawn::OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Error, TEXT("hit"));
    if (OtherActor->IsA(ProjectileClass))
    {
        if (Shield < 1)
        {
            this->Hp = Hp - 1;
            UE_LOG(LogTemp, Error, TEXT("by a projectile"));
            if(Hp <= 0)
            {
                this->Reset();
            }   
        }
        OtherActor->Destroy();
    }
    if (OtherActor->IsA(ASinglePowerupDrop::StaticClass()))
    {
        UE_LOG(LogTemp, Error, TEXT("by a powerupdrop"));
        for (int i = 0; i < MaxPowerupSlots; i++) 
        {
            if (Powerups[i] == PowerupsEnum::NONE) 
            {
                Powerups[i] = CastChecked<ASinglePowerupDrop>(OtherActor)->Powerup;
                OtherActor->Destroy();
                return;
            }
        }
    }
}

void AMyWheeledVehiclePawn::UseHeal() 
{
    Hp = MaxHp;
    UE_LOG(LogTemp, Warning, TEXT("healed"));
}

void AMyWheeledVehiclePawn::UseShield()
{
    this->SetShield(this->GetShield() + 1);
    FTimerHandle Timer;
    FTimerDelegate Delegate;
    Delegate.BindUObject(this, &AMyWheeledVehiclePawn::SetShield, this->GetShield()-1);
    GetWorld()->GetTimerManager().SetTimer(Timer,Delegate, 5.f, false);
    UE_LOG(LogTemp, Warning, TEXT("Shield started"));
}

void AMyWheeledVehiclePawn::UseProjectile()
{   
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();
    SpawnLocation = SpawnRotation.RotateVector(FVector(400, 0, 50)) + SpawnLocation;//spawns the projectile in front of the car, no matter the rotation
    GetWorld()->SpawnActor(this->ProjectileClass, &SpawnLocation, &SpawnRotation);
    return;
}

void AMyWheeledVehiclePawn::NextPowerupSlot()
{
    this->SetPowerupSlot(this->GetPowerupSlot() + 1);
}

void AMyWheeledVehiclePawn::UseBoost()
{
    this->GetMesh()->AddImpulse(this->GetActorRotation().RotateVector(FVector(1000, 0, 0)), "None", true);
}

int AMyWheeledVehiclePawn::GetMaxPowerupSlots()
{
    return MaxPowerupSlots;
}

void AMyWheeledVehiclePawn::DropPowerup()
{
    if (Powerups[PowerupSlot] == PowerupsEnum::NONE) 
    {
        return;
    }
    else
    {
        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();
        SpawnLocation = SpawnRotation.RotateVector(FVector(-400, 0, 50)) + SpawnLocation;//spawns the powerup behind the car, no matter the rotation
        if (Powerups[PowerupSlot] == PowerupsEnum::HEAL)
        {
            GetWorld()->SpawnActor(this->PowerupDrops[4], &SpawnLocation, &SpawnRotation);
            Powerups[PowerupSlot] = PowerupsEnum::NONE;
            return;
        }
        if (Powerups[PowerupSlot] == PowerupsEnum::SHIELD)
        {
            GetWorld()->SpawnActor(this->PowerupDrops[3], &SpawnLocation, &SpawnRotation);
            Powerups[PowerupSlot] = PowerupsEnum::NONE;
            return;
        }
        if (Powerups[PowerupSlot] == PowerupsEnum::BOOST)
        {
            GetWorld()->SpawnActor(this->PowerupDrops[1], &SpawnLocation, &SpawnRotation);
            Powerups[PowerupSlot] = PowerupsEnum::NONE;
            return;
        }
        if (Powerups[PowerupSlot] == PowerupsEnum::PROJECTILE)
        {
            GetWorld()->SpawnActor(this->PowerupDrops[2], &SpawnLocation, &SpawnRotation);
            Powerups[PowerupSlot] = PowerupsEnum::NONE;
            return;
        }
        
    }
}
