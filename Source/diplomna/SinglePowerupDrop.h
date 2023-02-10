// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PowerupsEnum.h"
#include "Components/StaticMeshComponent.h"

#include "SinglePowerupDrop.generated.h"

UCLASS()
class DIPLOMNA_API ASinglePowerupDrop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASinglePowerupDrop();

	UPROPERTY(EditAnywhere)
	PowerupsEnum Powerup = PowerupsEnum::NONE;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
