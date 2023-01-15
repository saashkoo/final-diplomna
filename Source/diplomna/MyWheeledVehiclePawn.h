// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "WheeledVehiclePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"

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
    AMyWheeledVehiclePawn();

    UPROPERTY(EditAnywhere)
    UCameraComponent* OurCameraComponent;

    UPROPERTY(EditAnywhere)
    USpringArmComponent* SpringArmComp;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

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


};
