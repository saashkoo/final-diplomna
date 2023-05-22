// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWheeledVehiclePawn.h"
#include "Components/BoxComponent.h"

AMyWheeledVehiclePawn::AMyWheeledVehiclePawn(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomVehicleMovementComponent>(VehicleMovementComponentName))
{
    RootComponent = GetMesh();
    CastMovementComp = Cast<UCustomVehicleMovementComponent>(GetVehicleMovementComponent());
    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("VehicleOverlapBox"));
    BoxComp->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
    OnActorBeginOverlap.AddDynamic(this, &AMyWheeledVehiclePawn::OnOverlap);
    BoxComp->SetupAttachment(RootComponent);
    bGenerateOverlapEventsDuringLevelStreaming = true;
    Powerups[0] = PowerupsEnum::NONE;
    Powerups[1] = PowerupsEnum::NONE;
    Powerups[2] = PowerupsEnum::NONE;
    MaxLaps = 0;
    CurrentLap = 1;
    ResetCheckpoint = nullptr;
    WrongDirectionCheckpoint = nullptr;
    CameraCycle = 0;
    ResetLocation = FVector(0.0f, 0.0f, 0.0f);
    ResetRotation = FRotator(0.0f, 0.0f, 0.0f);
    GetVehicleMovementComponent()->SetUseAutomaticGears(true);
    
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    //SpringArmComp->TargetArmLength = 300.0f;
    OurCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
    OurCameraComponent->SetupAttachment(SpringArmComp);
   


    

}

void AMyWheeledVehiclePawn::LoadGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
    if (LoadedGameData != nullptr) {
        UFastestTimeSaveGame* LoadedGame = CastChecked<UFastestTimeSaveGame>(LoadedGameData);
        {
            for (auto Result : LoadedGame->Times)
                UE_LOG(LogTemp, Error, TEXT("fastest time: %f, done by %s"), Result.Key, Result.Value.GetCharArray().GetData());
        }
    }
 }

void AMyWheeledVehiclePawn::BeginPlay()
{
    Super::BeginPlay();
    ResetLocation = GetActorLocation();
    MaxCameras = Cameras.Num();
    SetLapStartTime(GetGameTimeSinceCreation());
}


void AMyWheeledVehiclePawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (Hp <= 0)
    {
        Reset();
    }
    if (CastMovementComp) 
    {
        SpeedDelegate.ExecuteIfBound(CastMovementComp->GetSpeedKPH());
    }
    LapTimeDelegate.ExecuteIfBound(GetCurrentLapTime());
    //UE_LOG(LogTemp, Error, TEXT("a"));
    
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
    if (Cameras.Num() > 0) {
        auto It = Cameras.CreateIterator();
        for (int I = 0; I < CameraCycle; I++) {
            ++It;
        }
        OurCameraComponent->SetRelativeLocation((It).Key());
        OurCameraComponent->SetRelativeRotation(It.Value());
        CameraCycle = CameraCycle + 1;

        if (CameraCycle == MaxCameras) {
            CameraCycle = 0;
        }
    }
}

int AMyWheeledVehiclePawn::GetCamCycle()
{
    return CameraCycle;
}

void AMyWheeledVehiclePawn::SetCamCycle(int Cycle)
{
    while (Cycle > MaxCameras) {
        Cycle = Cycle - MaxCameras;
    }

    while (Cycle < 0) {
        Cycle = Cycle + MaxCameras;
    }
    CameraCycle = Cycle;
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
        SetHp(MaxHp);
        return;
    }

    //attempts to find a new spawn
    ResetLocation.Y = ResetLocation.Y + SpawnOffset;
    ResetLocation = ResetLocation + Offset;
    bTeleportSucceeded = MyWorld->FindTeleportSpot(this, ResetLocation, ResetRotation);
    ResetLocation = ResetLocation - Offset;
    if (bTeleportSucceeded)
    {
        GetMovementComponent()->Deactivate();
        TeleportTo(ResetLocation, ResetRotation);
        GetMovementComponent()->Activate();
        ResetLocation.Y = ResetLocation.Y - SpawnOffset;
        UE_LOG(LogTemp, Error, TEXT("end2 y = %f"), ResetLocation.Y);
        SetHp(MaxHp);
        return;
    }
    else 
    {
        ResetLocation.Y = ResetLocation.Y - SpawnOffset;
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
    LapDelegate.ExecuteIfBound(CurrentLap, MaxLaps);
}

void AMyWheeledVehiclePawn::SetCurrentLap(unsigned int LapCount)
{
    CurrentLap = LapCount;
    LapDelegate.ExecuteIfBound(CurrentLap, MaxLaps);
}

void AMyWheeledVehiclePawn::CompleteLap()
{
    float Seconds = GetGameTimeSinceCreation() - GetLapStartTime();
    int minutes = 0;
    if (FastestLap == -1)
    {
        FastestLap = Seconds;
    }
    if (Seconds < FastestLap)
    {
        FastestLap = Seconds;
    }
     SetLapStartTime(GetGameTimeSinceCreation());
    
    if (CurrentLap == MaxLaps) 
    {
        UE_LOG(LogTemp, Error, TEXT("Finished race"));
        HasWon = true;
        Cast<AGameMode>(GetWorld()->GetAuthGameMode())->EndMatch();
    }
    CurrentLap++;
    LapDelegate.ExecuteIfBound(CurrentLap, MaxLaps);
}

float AMyWheeledVehiclePawn::GetFastestTime()
{
    return FastestLap;
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
    int PowerupVal = 0;
    switch (Value)
    {
    case PowerupsEnum::HEAL:
        PowerupVal = 4;
        break;
    case PowerupsEnum::SHIELD:
        PowerupVal = 3;
        break;
        return;
    case PowerupsEnum::BOOST:
        PowerupVal = 1;
        break;
        return;
    case PowerupsEnum::PROJECTILE:
        PowerupVal = 2;
        break;
    }
    PowerupDelegate.ExecuteIfBound(Slot,PowerupVal);
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
    HpDelegate.ExecuteIfBound(Value, MaxHp);
}

int AMyWheeledVehiclePawn::GetHp()
{
    return Hp;
}

void AMyWheeledVehiclePawn::UseSelectedPowerup()
{
    switch (Powerups[PowerupSlot])
    {
    case PowerupsEnum::HEAL:
        UseHeal();
        SetPowerup(PowerupsEnum::NONE, PowerupSlot);
        return;
    case PowerupsEnum::SHIELD:
        UseShield();
        SetPowerup(PowerupsEnum::NONE, PowerupSlot);
        return;
    case PowerupsEnum::BOOST:
        UseBoost();
        SetPowerup(PowerupsEnum::NONE, PowerupSlot);
        return;
    case PowerupsEnum::PROJECTILE:
        UseProjectile();
        SetPowerup(PowerupsEnum::NONE, PowerupSlot);
        return;
    case PowerupsEnum::NONE:
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
    SelectedPowerupDelegate.ExecuteIfBound(Value);
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
    UE_LOG(LogTemp, Warning, TEXT("Shield: %d"), GetShield());
}

int AMyWheeledVehiclePawn::GetShield()
{
    return Shield;
}

void AMyWheeledVehiclePawn::OnOverlap(class AActor* Actor, class AActor* OtherActor)
{
    UE_LOG(LogTemp, Error, TEXT("hit"));
    if (OtherActor->IsA(ProjectileClass))
    {
        if (Shield < 1)
        {
            SetHp(GetHp() - 1);
            UE_LOG(LogTemp, Error, TEXT("by a projectile"));
            if(Hp <= 0)
            {
                Reset();
            }   
        }
        OtherActor->Destroy();
    }
    if (OtherActor->IsA(ASinglePowerupDrop::StaticClass()))
    {
        UE_LOG(LogTemp, Error, TEXT("by a powerupdrop"));
        for (int I = 0; I < MaxPowerupSlots; I++) 
        {
            if (Powerups[I] == PowerupsEnum::NONE) 
            {
                SetPowerup(CastChecked<ASinglePowerupDrop>(OtherActor)->Powerup, I);
                OtherActor->Destroy();
                return;
            }
        }
    }
}

void AMyWheeledVehiclePawn::UseHeal() 
{
    SetHp(MaxHp);
    UE_LOG(LogTemp, Warning, TEXT("healed"));
}

void AMyWheeledVehiclePawn::UseShield()
{
    SetShield(GetShield() + 1);
    FTimerHandle Timer;
    FTimerDelegate Delegate;
    Delegate.BindUObject(this, &AMyWheeledVehiclePawn::SetShield, GetShield()-1);
    GetWorld()->GetTimerManager().SetTimer(Timer,Delegate, 5.f, false);
    UE_LOG(LogTemp, Warning, TEXT("Shield started"));
}

void AMyWheeledVehiclePawn::UseProjectile()
{   
    FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("ProjectileSpawnerSocket"));
    FRotator SpawnRotation = GetMesh()->GetSocketRotation(FName("ProjectileSpawnerSocket"));
    GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);
    return;
}

void AMyWheeledVehiclePawn::NextPowerupSlot()
{
    SetPowerupSlot(GetPowerupSlot() + 1);
}

void AMyWheeledVehiclePawn::UseBoost()
{
    GetMesh()->AddImpulse(GetActorRotation().RotateVector(FVector(1000, 0, 0)), "None", true);
}

float AMyWheeledVehiclePawn::GetLapStartTime()
{
    return LapStartTime;
}

void AMyWheeledVehiclePawn::SetLapStartTime(float Time)
{
    LapStartTime = Time;
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
        FVector SpawnLocation = GetMesh()->GetSocketLocation(FName("PowerupDropSpawnerSocket"));
        FRotator SpawnRotation = GetMesh()->GetSocketRotation(FName("PowerupDropSpawnerSocket"));
        switch (Powerups[PowerupSlot])
        {
            case PowerupsEnum::HEAL:
                GetWorld()->SpawnActor(PowerupDrops[4], &SpawnLocation, &SpawnRotation);
                SetPowerup(PowerupsEnum::NONE, PowerupSlot);
                return;
            case PowerupsEnum::SHIELD:
                GetWorld()->SpawnActor(PowerupDrops[3], &SpawnLocation, &SpawnRotation);
                SetPowerup(PowerupsEnum::NONE, PowerupSlot);
                return;
            case PowerupsEnum::BOOST:
                GetWorld()->SpawnActor(PowerupDrops[1], &SpawnLocation, &SpawnRotation);
                SetPowerup(PowerupsEnum::NONE, PowerupSlot);
                return;
            case PowerupsEnum::PROJECTILE:
                GetWorld()->SpawnActor(PowerupDrops[2], &SpawnLocation, &SpawnRotation);
                SetPowerup(PowerupsEnum::NONE, PowerupSlot);
                return;
        }   
    }
}

int AMyWheeledVehiclePawn::GetSpeedKPH()
{
    int RetVal = int(GetVehicleMovementComponent()->GetForwardSpeed() * 0.036);
    if (RetVal)
    { 
        if (RetVal < 0)
        {
            return -RetVal;
        }
        else
        {
            return RetVal;
        }
        
    }
    else
    {
        return 0;
    }
    
}

FString AMyWheeledVehiclePawn::GetCurrentLapTime()
{
    float Time = GetGameTimeSinceCreation() - GetLapStartTime();
    int Minutes = 0;
    while (Time > 60.0) {
        Minutes++;
        Time -= 60;
    }
    FString StringTime = FString::Printf(TEXT("%2d.%2.2f"), Minutes, Time);
    if (!StringTime.IsEmpty())
    {
        return StringTime;
    }
    else
    {
        return FString("00.00.00");
    }
}