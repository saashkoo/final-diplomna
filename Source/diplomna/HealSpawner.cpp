// Fill out your copyright notice in the Description page of Project Settings.


#include "HealSpawner.h"

AHealSpawner::AHealSpawner() 
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("HealSpawner"));
	BoxComp->BodyInstance.SetCollisionProfileName("Trigger");
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APowerupSpawner::OnOverlapBegin);

	RootComponent = BoxComp;
	Powerup = PowerupsEnum::HEAL;
}
