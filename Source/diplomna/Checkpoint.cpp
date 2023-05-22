// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	OnActorBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);

	RootComponent = BoxComp;
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACheckpoint::OnOverlapBegin(class AActor* Actor, class AActor* OtherActor)
{
	if ((OtherActor->ActorHasTag(FName("Player"))))
	{
		AMyWheeledVehiclePawn* Player = CastChecked<AMyWheeledVehiclePawn>(OtherActor);
		if (Player->GetWrongDirectionCheckpoint() == this) 
		{
			UE_LOG(LogTemp, Error, TEXT("sad"));
			Player->Reset();
			return;
		}
		if (Player->GetResetCheckpoint() != this)
		{
			UE_LOG(LogTemp, Error, TEXT("%s passed a checkpoint"), *(OtherActor->GetActorNameOrLabel()));
			Player->SetResetCheckpoint(this);
		}
		
	}
}
