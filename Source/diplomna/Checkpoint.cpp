// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->BodyInstance.SetCollisionProfileName("Trigger");
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);

	RootComponent = BoxComp;
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACheckpoint::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherComp != NULL) && ((OtherActor->GetActorNameOrLabel() == "BP_CAR_MyWheeledVehiclePawn")|| (OtherActor->GetActorNameOrLabel() == "BP_CAR_MyWheeledVehiclePawn1")))
	{
		UE_LOG(LogTemp, Error, TEXT("%s passed a checkpoint"), *(OtherActor->GetActorNameOrLabel()));
		AMyWheeledVehiclePawn* Player = Cast<AMyWheeledVehiclePawn>(OtherActor);
		Player->SetResetLocation(this->GetActorLocation(), this->GetActorRotation());
	}
}
