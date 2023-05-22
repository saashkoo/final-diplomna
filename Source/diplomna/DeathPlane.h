// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyWheeledVehiclePawn.h"
#include "DeathPlane.generated.h"

UCLASS()
class DIPLOMNA_API ADeathPlane : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
		class UBoxComponent* BoxComp;

	UFUNCTION()
		virtual void OnOverlapBegin(class AActor* Actor, class AActor* OtherActor);

};