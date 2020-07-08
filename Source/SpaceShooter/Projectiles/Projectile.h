// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h "
#include "Particles/ParticleSystem.h"
#include "Projectile.generated.h"

UCLASS()
class SPACESHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when an instance of this class is placed (in editor) or spawned
	virtual void OnConstruction(const FTransform& Transform) override;

	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material = nullptr;

	UPROPERTY(EditAnywhere)
		UMaterialInstanceDynamic* DynMaterial = nullptr;
	
	UPROPERTY(EditAnywhere)
		FVector Scale = FVector(1.F, 1.F, 1.F);
	
	UPROPERTY(EditAnywhere)
		float Speed = 1000.F;

	UPROPERTY(EditAnywhere)
		float Damage = 100.F;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* ExplosionParticleSystem = LoadObject<UParticleSystem>(NULL, TEXT("/Game/Assets/Particles/P_Pixel_Explosion.P_Pixel_Explosion"), NULL, LOAD_None, NULL);

public:
	UPROPERTY(EditAnywhere)
		FLinearColor ProjectileColor = FLinearColor::White ;

protected:
	UFUNCTION()
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	
};
