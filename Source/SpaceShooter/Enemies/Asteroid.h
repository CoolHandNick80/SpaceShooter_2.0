// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameModes/MyGameModeBase.h"
#include "GameInstances/MyGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h "
#include "Particles/ParticleSystem.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Asteroid.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when an instance of this class is placed (in editor) or spawned
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called after the Actor's components have been initialized
	virtual void PostInitializeComponents() override;

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

	UPROPERTY(VisibleAnywhere)
		UArrowComponent* ArrowComponent = nullptr;

	UPROPERTY(EditAnywhere)
		float MaxHealth = 100.F;

	UPROPERTY(EditAnywhere)
		float Health = 0.F;

	UPROPERTY(EditAnywhere, category = Movement)
		float MinSpeed = 25.F;

	UPROPERTY(EditAnywhere, category = Movement)
		float MaxSpeed = 250.F;

	UPROPERTY(EditAnywhere)
		float Speed = 1000.F;

	UPROPERTY(EditAnywhere)
		int32 EnemyScoreValue = 5.F;
	
	UPROPERTY()
		float DamageValue = 5.F;

	UPROPERTY()
		AMyGameModeBase* GameMode = nullptr;

	UPROPERTY()
		UMyGameInstance* GameInstance = nullptr;

	UPROPERTY(EditAnywhere)
		FVector Scale = FVector::OneVector;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* ExplosionParticleSystem = LoadObject<UParticleSystem>(NULL, TEXT("/Game/Assets/Particles/P_Pixel_Explosion_Player.P_Pixel_Explosion_Player"), NULL, LOAD_None, NULL);

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LifeTime = 10.F;

protected:
	void SetUpScale(FVector InScale);

	UFUNCTION()
		void OnEnemyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void StartTimer();

	void Explode();
};
