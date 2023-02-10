// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupSpawner.h"

// Sets default values
APowerupSpawner::APowerupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawner"));
	BoxComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APowerupSpawner::OnOverlapBegin);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->BodyInstance.SetCollisionProfileName("OverlapAll");
	RootComponent = BoxComp;
	Mesh->AttachToComponent(BoxComp, FAttachmentTransformRules::KeepRelativeTransform);
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

void APowerupSpawner::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCanBeCollected) {
		if ((OtherComp != NULL) && ((OtherActor->GetActorNameOrLabel() == "BP_CAR_MyWheeledVehiclePawn") || (OtherActor->GetActorNameOrLabel() == "BP_CAR_MyWheeledVehiclePawn1")))
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