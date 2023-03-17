// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalCheckpoint.h"

AFinalCheckpoint::AFinalCheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("FinalBoxComp"));
	BoxComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFinalCheckpoint::OnOverlapBegin);

	RootComponent = BoxComp;
}


void AFinalCheckpoint::BeginPlay()
{
	Super::BeginPlay();

}


void AFinalCheckpoint::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if ((OtherComp != NULL) && OtherActor->ActorHasTag(FName("Player")))
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