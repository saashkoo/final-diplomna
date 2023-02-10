// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "WheeledVehiclePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "CustomVehicleMovementComponent.h"
#include "PowerupsEnum.h"
#include "Projectile.h"
#include "SinglePowerupDrop.h"
#include "Containers/Array.h"

#include "MyWheeledVehiclePawn.generated.h"



/**
 * 
 */
UCLASS()
class DIPLOMNA_API AMyWheeledVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
public:
    // Sets default values
    AMyWheeledVehiclePawn(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditAnywhere)
    UCameraComponent* OurCameraComponent;

    UPROPERTY(EditAnywhere)
    USpringArmComponent* SpringArmComp;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<ASinglePowerupDrop>> PowerupDrops;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY()
    UCustomVehicleMovementComponent* NewVehicleMovementComponent;
    
    UPROPERTY(EditAnywhere)
    unsigned int MaxLaps;

    UPROPERTY(EditAnywhere)
    unsigned int CurrentLap;

    UPROPERTY(EditAnywhere)
    int camera_cycle;

    UPROPERTY(EditAnywhere)
    int max_cameras = 2;

    UPROPERTY(EditAnywhere)
    float spawn_offset = 500.0f;

    UPROPERTY(EditAnywhere)
    FVector ResetLocation;

    UPROPERTY(EditAnywhere)
    FRotator ResetRotation;

    UPROPERTY(EditAnywhere)
    AActor* ResetCheckpoint;

    UPROPERTY(EditAnywhere)
    AActor* WrongDirectionCheckpoint;

    UPROPERTY(EditAnywhere)
    PowerupsEnum Powerups[3];

    UPROPERTY(EditAnywhere)
    int Hp = 3;

    UPROPERTY(EditAnywhere)
    int MaxHp = 3;

    UPROPERTY(EditAnywhere)
    int Shield = 0;

    UPROPERTY(EditAnywhere)
    int PowerupSlot = 0;

    UPROPERTY(EditAnywhere)
    int MaxPowerupSlots = 3;

public:
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
    
    UFUNCTION()
    void Accelerate(float AxisValue);

    UFUNCTION()
    void Steer(float AxisValue);
    
    UFUNCTION()
    void ChangeCam();
    
    UFUNCTION()
    int GetCamCycle();
    
    UFUNCTION()
    void SetCamCycle(int cycle);
    
    UFUNCTION()
    void SetResetLocation(FVector NewLocation, FRotator NewRotation);
    
    UFUNCTION()
    void Reset();

    UFUNCTION()
    AActor* GetResetCheckpoint();

    UFUNCTION()
    AActor* GetWrongDirectionCheckpoint();

    UFUNCTION()
    void SetResetCheckpoint(AActor * NewCheckpoint);

    UFUNCTION()
    void SetWrongDirectionCheckpoint(AActor* NewCheckpoint);

    UFUNCTION()
    void SetMaxLaps(unsigned int LapCount);

    UFUNCTION()
    void SetCurrentLap(unsigned int LapCount);

    UFUNCTION()
    void CompleteLap();

    UFUNCTION()
    unsigned int GetMaxLaps();

    UFUNCTION()
    unsigned int GetCurrentLap();

    UFUNCTION()
    void SetPowerup(PowerupsEnum Value, int Slot);

    UFUNCTION()
    PowerupsEnum GetPowerup(int Slot);

    UFUNCTION()
    int GetHp();

    UFUNCTION()
    void SetHp(int Value);

    UFUNCTION()
    void UseSelectedPowerup();

    UFUNCTION()
    int GetPowerupSlot();

    UFUNCTION()
    void SetPowerupSlot(int Value);

    UFUNCTION()
    int GetShield();

    UFUNCTION()
    void SetShield(int Value);

    UFUNCTION()
    int GetMaxPowerupSlots();

    UFUNCTION()
    void NextPowerupSlot();

    UFUNCTION()
    void OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void DropPowerup();

public://to be changed
    UFUNCTION()
    void UseShield();

    UFUNCTION()
    void UseProjectile();

    UFUNCTION()
    void UseHeal();

    UFUNCTION()
    void UseBoost();

};
