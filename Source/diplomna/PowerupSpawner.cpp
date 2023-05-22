// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupSpawner.h"

// Sets default values
APowerupSpawner::APowerupSpawner()
{

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawner"));
	BoxComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	OnActorBeginOverlap.AddDynamic(this, &APowerupSpawner::OnOverlapBegin);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->BodyInstance.SetCollisionProfileName("NoCollision");
	RootComponent = BoxComp;
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APowerupSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void APowerupSpawner::OnOverlapBegin(class AActor* Actor, class AActor* OtherActor)
{

	if (bCanBeCollected) {
		if (OtherActor->ActorHasTag(FName("Player")))
		{
			AMyWheeledVehiclePawn* Player = CastChecked<AMyWheeledVehiclePawn>(OtherActor);
			for (int I = 0; I < Player->GetMaxPowerupSlots(); I++)
			{
				if (Player->GetPowerup(I) == PowerupsEnum::NONE)
				{
					Player->SetPowerup(Powerup, I);
					bCanBeCollected = false;
					FTimerHandle Handle;
					GetWorld()->GetTimerManager().SetTimer(Handle, this, &APowerupSpawner::Respawn, 2.f, false);
					this->Mesh->SetVisibility(false, false);
					return;
				}
			}
		}
	}
}

void APowerupSpawner::Respawn()
{
	bCanBeCollected = true;
	this->Mesh->SetVisibility(true, false);
}