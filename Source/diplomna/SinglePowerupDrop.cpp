// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePowerupDrop.h"

// Sets default values
ASinglePowerupDrop::ASinglePowerupDrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

// Called every frame
void ASinglePowerupDrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

