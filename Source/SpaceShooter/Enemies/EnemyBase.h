// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameModes/MyGameModeBase.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/EnemyAnimComponent.h"
#include "Components/EnemyMovementComponent.h"
#include "Components/EnemyFireComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/EnemyHealthBar.h"
#include "Widgets/EnemyHealthBarWidget.h"

#include "EnemyBase.generated.h"

class AMyTriggerBox;

UCLASS()
class SPACESHOOTER_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBase();

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
		UEnemyAnimComponent* SpawnAnimation = nullptr;

	UPROPERTY(VisibleAnywhere)
		UEnemyMovementComponent* MovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UEnemyFireComponent* FireComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UEnemyHealthBar* EnemyHealthBar = nullptr;
	
	


	UPROPERTY(EditAnywhere)
		float MaxHealth = 100.F;
	
	UPROPERTY(EditAnywhere)
		float Health = 0.F;

	UPROPERTY(EditAnywhere, category = Movement)
		float MinSpeed = 25.F;

	UPROPERTY(EditAnywhere, category = Movement)
		float MaxSpeed = 250.F;

	UPROPERTY(EditAnywhere, category = Movement)
		float DistanceFromPlayer = 120.F;

	UPROPERTY(EditDEfaultsOnly, Category = Fire)
		FColor ProjectileColor = FColor::Blue;

	UPROPERTY(EditDEfaultsOnly, BlueprintReadWrite, Category = Fire)
		TSubclassOf<AProjectile> ProjectileClass = nullptr;
	
	UPROPERTY()
		AMyGameModeBase* GameMode = nullptr;

	UPROPERTY(EditAnywhere)
		FVector Scale = FVector::OneVector;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* ExplosionParticleSystem = LoadObject<UParticleSystem>(NULL, TEXT("/Game/Assets/Particles/P_Pixel_Explosion_Player.P_Pixel_Explosion_Player"), NULL, LOAD_None, NULL);

	UPROPERTY()
		float DamageValue = 0.5F;

public:
	
	UPROPERTY(EditAnywhere)
		bool bMoveEnabled = false;

	UPROPERTY()
		AMyTriggerBox* MyTriggerBox = nullptr;

protected:

	void SetUpValues();
	
	void SetUpScale(FVector InScale);

	void UpdateHealth();

	UFUNCTION()
		void OnEnemyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//UFUNCTION()
		//void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:
	
	float GetMaxDistanceFromPlayer() { return DistanceFromPlayer; }

	float GetEnemyHealth() { return Health; }

	float GetEnemyMaxHealth() { return MaxHealth; }

protected:

	UEnemyHealthBarWidget* EnemyHealthBarWidget = nullptr;


};
