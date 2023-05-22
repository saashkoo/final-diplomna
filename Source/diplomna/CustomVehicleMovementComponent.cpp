// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomVehicleMovementComponent.h"


void UCustomVehicleMovementComponent::SetForwardSpeed(float Speed) 
{
	VehicleState.ForwardsAcceleration = VehicleState.ForwardsAcceleration + 10000;
}


int UCustomVehicleMovementComponent::GetSpeedKPH()
{
    int RetVal = int(GetForwardSpeed() * 0.036);
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