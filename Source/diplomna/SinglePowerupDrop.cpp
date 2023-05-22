// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePowerupDrop.h"

// Sets default values
ASinglePowerupDrop::ASinglePowerupDrop()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BoxComp;
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}


// Called when the game starts or when spawned
void ASinglePowerupDrop::BeginPlay()
{
	Super::BeginPlay();
	
}


