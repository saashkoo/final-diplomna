// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerupsEnum.generated.h"

UENUM(BlueprintType)
enum class PowerupsEnum : uint8
{
	NONE = 0 UMETA(DisplayName = "None"),
	BOOST = 1 UMETA(DisplayName = "Boost"),
	PROJECTILE = 2 UMETA(DisplayName = "Projectile"),
	SHIELD = 3 UMETA(DisplayName = "Shiled"),
	HEAL = 4 UMETA(DisplayName = "Heal")
};
/**
 * 
 */
