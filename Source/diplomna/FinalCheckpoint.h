// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"

#include "FinalCheckpoint.generated.h"

/**
 * 
 */
UCLASS()
class DIPLOMNA_API AFinalCheckpoint : public ACheckpoint
{
	GENERATED_BODY()

public:
	AFinalCheckpoint();
	
protected:
	virtual void BeginPlay() override;

public:
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
