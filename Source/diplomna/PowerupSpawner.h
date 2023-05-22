// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWheeledVehiclePawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "PowerupSpawner.generated.h"

UCLASS()
class DIPLOMNA_API APowerupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerupSpawner();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	PowerupsEnum Powerup = PowerupsEnum::NONE;

	bool bCanBeCollected = true;

public:	

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UFUNCTION()
	void OnOverlapBegin(class AActor* Actor, class AActor* OtherActor);

	UFUNCTION()
		void Respawn();
};
