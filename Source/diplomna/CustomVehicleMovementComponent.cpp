// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVehicleMovementComponent.h"


void UCustomVehicleMovementComponent::SetForwardSpeed(float Speed) 
{
	VehicleState.ForwardsAcceleration = VehicleState.ForwardsAcceleration + 10000;
}
