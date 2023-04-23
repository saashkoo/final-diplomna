// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWheeledVehiclePawn.h"
#include "Components/BoxComponent.h"

AMyWheeledVehiclePawn::AMyWheeledVehiclePawn(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomVehicleMovementComponent>(VehicleMovementComponentName))
{
    RootComponent = GetMesh();
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
    SpringArmComp->TargetArmLength = 300.0f;
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
    SetLapStartTime(GetGameTimeSinceCreation());
}


void AMyWheeledVehiclePawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if(Hp <= 0)
    {
        Reset();
    }
    SpeedDelegate.Execute(GetSpeedKPH());
    LapTimeDelegate.Execute(GetCurrentLapTime());
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
    UE_LOG(LogTemp, Error, TEXT("gear: %d"), GetVehicleMovementComponent()->GetCurrentGear());
    UE_LOG(LogTemp, Error, TEXT("speed: %f"), GetVehicleMovementComponent()->GetForwardSpeedMPH());
    UE_LOG(LogTemp, Error, TEXT("usesautogear: %d"), GetVehicleMovementComponent()->GetUseAutoGears());
    

    if (CameraCycle == 0) {
        OurCameraComponent->SetRelativeLocation(FVector(200.0f, 0.0f, 100.0f));
        OurCameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    }
    if (CameraCycle == 1) {
        OurCameraComponent->SetRelativeLocation(FVector(-450.0f, 0.0f, 350.0f));
        OurCameraComponent->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
    }
    CameraCycle = CameraCycle + 1;

    if (CameraCycle == MaxCameras) {
        CameraCycle = 0;
    }
}

int AMyWheeledVehiclePawn::GetCamCycle()
{
    return CameraCycle;
}

void AMyWheeledVehiclePawn::SetCamCycle(int cycle)
{
    while (cycle > MaxCameras) {
        cycle = cycle - MaxCameras;
    }

    while (cycle < 0) {
        cycle = cycle + MaxCameras;
    }
    CameraCycle = cycle;
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
    ResetLocation.Y = ResetLocation.Y + spawn_offset;
    ResetLocation = ResetLocation + Offset;
    bTeleportSucceeded = MyWorld->FindTeleportSpot(this, ResetLocation, ResetRotation);
    ResetLocation = ResetLocation - Offset;
    if (bTeleportSucceeded)
    {
        GetMovementComponent()->Deactivate();
        TeleportTo(ResetLocation, ResetRotation);
        GetMovementComponent()->Activate();
        ResetLocation.Y = ResetLocation.Y - spawn_offset;
        UE_LOG(LogTemp, Error, TEXT("end2 y = %f"), ResetLocation.Y);
        SetHp(MaxHp);
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
    LapDelegate.Execute(CurrentLap, MaxLaps);
}

void AMyWheeledVehiclePawn::SetCurrentLap(unsigned int LapCount)
{
    CurrentLap = LapCount;
    LapDelegate.Execute(CurrentLap, MaxLaps);
}

void AMyWheeledVehiclePawn::CompleteLap()
{
    float seconds = GetGameTimeSinceCreation() - GetLapStartTime();
    int minutes = 0;
    if (FastestLap == -1)
    {
        FastestLap = seconds;
    }
    if (seconds < FastestLap)
    {
        FastestLap = seconds;
    }
    while (seconds > 60.f) 
    {
        minutes = minutes + 1;
        seconds = seconds - 60.f;
    }
     UE_LOG(LogTemp, Warning, TEXT("LapTime: %2d.%2.2f"), minutes, seconds);
     SetLapStartTime(GetGameTimeSinceCreation());
    
    if (CurrentLap == MaxLaps) 
    {
        UE_LOG(LogTemp, Error, TEXT("Finished race"));
        if (UFastestTimeSaveGame* LoadedGame = Cast<UFastestTimeSaveGame>(UGameplayStatics::LoadGameFromSlot("defalut", 0)))
        {
            LoadedGame->Times.Add(FastestLap, GetActorNameOrLabel());
            LoadedGame->Times.KeySort([](float A, float B) { return A < B; });
        }
        else if(UFastestTimeSaveGame* SaveGameInstance = Cast<UFastestTimeSaveGame>(UGameplayStatics::CreateSaveGameObject(UFastestTimeSaveGame::StaticClass())))
        {
            SaveGameInstance->Times.Add(FastestLap, GetActorNameOrLabel());
            SaveGameInstance->Times.KeySort([](float A, float B) { return A < B; });
            if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, "defalut", 0))
            {
                
            }
        }
        CastChecked<AGameMode>(GetWorld()->GetAuthGameMode())->EndMatch();
    }
    CurrentLap++;
    LapDelegate.Execute(CurrentLap, MaxLaps);
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
    if (Value == PowerupsEnum::BOOST) { PowerupVal = 1; }
    if (Value == PowerupsEnum::PROJECTILE) { PowerupVal = 2; }
    if (Value == PowerupsEnum::SHIELD) { PowerupVal = 3; }
    if (Value == PowerupsEnum::HEAL) { PowerupVal = 4; }
    PowerupDelegate.Execute(Slot,PowerupVal);
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
    HpDelegate.Execute(Value, MaxHp);
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
        SetPowerup(PowerupsEnum::NONE, PowerupSlot);
        //Powerups[PowerupSlot] = PowerupsEnum::NONE;
        return;
    }
    if (Powerups[PowerupSlot] == PowerupsEnum::SHIELD)
    {
        UseShield();
        SetPowerup(PowerupsEnum::NONE, PowerupSlot);
        return;
    }
    if (Powerups[PowerupSlot] == PowerupsEnum::BOOST)
    {
        UseBoost();
        SetPowerup(PowerupsEnum::NONE, PowerupSlot);
        return;
    }
    if (Powerups[PowerupSlot] == PowerupsEnum::PROJECTILE)
    {
        UseProjectile();
        SetPowerup(PowerupsEnum::NONE, PowerupSlot);
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
    SelectedPowerupDelegate.Execute(Value);
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
        for (int i = 0; i < MaxPowerupSlots; i++) 
        {
            if (Powerups[i] == PowerupsEnum::NONE) 
            {
                SetPowerup(CastChecked<ASinglePowerupDrop>(OtherActor)->Powerup, i);
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
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();
    SpawnLocation = SpawnRotation.RotateVector(FVector(400, 0, 50)) + SpawnLocation;//spawns the projectile in front of the car, no matter the rotation
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
        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();
        SpawnLocation = SpawnRotation.RotateVector(FVector(-400, 0, 50)) + SpawnLocation;//spawns the powerup behind the car, no matter the rotation
        if (Powerups[PowerupSlot] == PowerupsEnum::HEAL)
        {
            GetWorld()->SpawnActor(PowerupDrops[4], &SpawnLocation, &SpawnRotation);
            SetPowerup(PowerupsEnum::NONE, PowerupSlot);
            return;
        }
        if (Powerups[PowerupSlot] == PowerupsEnum::SHIELD)
        {
            GetWorld()->SpawnActor(PowerupDrops[3], &SpawnLocation, &SpawnRotation);
            SetPowerup(PowerupsEnum::NONE, PowerupSlot);
            return;
        }
        if (Powerups[PowerupSlot] == PowerupsEnum::BOOST)
        {
            GetWorld()->SpawnActor(PowerupDrops[1], &SpawnLocation, &SpawnRotation);
            SetPowerup(PowerupsEnum::NONE, PowerupSlot);
            return;
        }
        if (Powerups[PowerupSlot] == PowerupsEnum::PROJECTILE)
        {
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