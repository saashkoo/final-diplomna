// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalCheckpoint.h"

AFinalCheckpoint::AFinalCheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("FinalBoxComp"));
	BoxComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	//OnActorBeginOverlap.AddDynamic(this, &AFinalCheckpoint::OnOverlapBegin);
	SetRootComponent(BoxComp);
}


void AFinalCheckpoint::BeginPlay()
{
	Super::BeginPlay();

}


void AFinalCheckpoint::OnOverlapBegin(class AActor* Actor, class AActor* OtherActor)
{

	if (OtherActor->ActorHasTag(FName("Player")))
	{
		AMyWheeledVehiclePawn* Player = CastChecked<AMyWheeledVehiclePawn>(OtherActor);
		if (Player->GetWrongDirectionCheckpoint() == this)
		{
			UE_LOG(LogTemp, Error, TEXT("wtf"));
			Player->Reset();
			return;
		}
		if (Player->GetResetCheckpoint() != this)
		{
			UE_LOG(LogTemp, Error, TEXT("%s passed the finish line"), *(OtherActor->GetActorNameOrLabel()));
			Player->CompleteLap();
			Player->SetResetCheckpoint(this);
		}

	}
}