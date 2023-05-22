// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->MaxSpeed = 1001.f;
	MovementComponent->InitialSpeed = 1000.f;
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	OnActorBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BoxComp;
	Mesh->SetupAttachment(RootComponent);
	MovementComponent->ProjectileGravityScale = 0.f;
	MovementComponent->Velocity = this->GetActorRotation().RotateVector(FVector(1, 0, 0));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::OnOverlapBegin(class AActor* Actor, class AActor* OtherActor)
{
	for (auto It = IgnoredClasses.CreateConstIterator(); It; ++It)
	{
		if(OtherActor->IsA(*It))
		{
			return;
		}
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
	this->Destroy();
}
