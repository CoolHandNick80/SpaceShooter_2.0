// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Materials/MaterialInstanceDynamic.h "
#include "Engine/Engine.h"
#include "Pawns/MyPawn.h"
#include "PlayerControllers/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


// Sets default values
AProjectile::AProjectile()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	DynMaterial = UMaterialInstanceDynamic::Create(Material, this);
	DynMaterial->SetVectorParameterValue(FName("Color"), ProjectileColor);

	StaticMeshComponent->SetMaterial(0, DynMaterial);
	StaticMeshComponent->SetWorldScale3D(Scale);

	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->Velocity = FVector::ForwardVector;
	ProjectileMovementComponent->ProjectileGravityScale = 0.F;
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnProjectileHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor != nullptr)
	{
		if (OtherActor->IsA(AMyPawn::StaticClass()))
		{
			AMyPawn* MyPawn = Cast<AMyPawn>(OtherActor);
			if (MyPawn != nullptr)
			{
				AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
				if (MyPlayerController != nullptr)
				{
					UGameplayStatics::ApplyDamage(MyPawn, Damage, MyPlayerController, this, UDamageType::StaticClass());
				}
			}			
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, this, UDamageType::StaticClass());
		}
	}
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, Hit.Location, FRotator::ZeroRotator, true);

	Destroy();
}