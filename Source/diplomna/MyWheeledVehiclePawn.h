// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "WheeledVehiclePawn.h"
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

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere)
    int camera_cycle;

    UPROPERTY(EditAnywhere)
    FVector ResetLocation;

    UPROPERTY(EditAnywhere)
    FRotator ResetRotation;

public:
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
    
    void Accelerate(float AxisValue);
    void Steer(float AxisValue);
    void ChangeCam();
    int GetCamCycle();
    void SetCamCycle(int cycle);
    void SetResetLocation(FVector NewLocation, FRotator NewRotation);
    void Reset();
 
};
