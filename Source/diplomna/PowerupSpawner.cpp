// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupSpawner.h"

// Sets default values
APowerupSpawner::APowerupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

// Called every frame
void APowerupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerupSpawner::OnOverlapBegin(class AActor* Actor, class AActor* OtherActor)
{

	if (bCanBeCollected) {
		if (OtherActor->ActorHasTag(FName("Player")))
		{
			AMyWheeledVehiclePawn* Player = CastChecked<AMyWheeledVehiclePawn>(OtherActor);
			for (int i = 0; i < Player->GetMaxPowerupSlots(); i++)
			{
				if (Player->GetPowerup(i) == PowerupsEnum::NONE)
				{
					Player->SetPowerup(Powerup, i);
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