// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathPlane.h"

// Sets default values
ADeathPlane::ADeathPlane()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	OnActorBeginOverlap.AddDynamic(this, &ADeathPlane::OnOverlapBegin);

	RootComponent = BoxComp;
}


// Called when the game starts or when spawned
void ADeathPlane::BeginPlay()
{
	Super::BeginPlay();
	
}


void ADeathPlane::OnOverlapBegin(class AActor* Actor, class AActor* OtherActor)
{
	if ((OtherActor->ActorHasTag(FName("Player"))))
	{
		AMyWheeledVehiclePawn* Player = CastChecked<AMyWheeledVehiclePawn>(OtherActor);
		if (Player)
		{
			Player->SetHp(0);
			return;
		}
	}
}