// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldSpawner.h"

AShieldSpawner::AShieldSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("ShieldSpawner"));
	BoxComp->BodyInstance.SetCollisionProfileName("Trigger");
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APowerupSpawner::OnOverlapBegin);

	RootComponent = BoxComp;
	Powerup = PowerupsEnum::SHIELD;
}