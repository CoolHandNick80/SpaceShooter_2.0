// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Components/TimelineComponent.h"
#include "Projectiles/Projectile.h"
#include "Components/MyPawnMovementComponent.h"
#include "Components/SpawnAnimComponent.h"
#include "Components/FireComponent.h"
#include "Components/CrossHairComponent.h"
#include "MyPawn.generated.h"

class UMyGameInstance;
UCLASS()
class SPACESHOOTER_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called after the Actor's components have been initialized
	virtual void PostInitializeComponents() override;
	
// Pointers to components
protected:
	/*UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent = nullptr;*/

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UFireComponent* PrimaryFireSpawn = nullptr;

	UPROPERTY(VisibleAnywhere)
		UFireComponent* SecondaryFireLeft = nullptr;

	UPROPERTY(VisibleAnywhere)
		UFireComponent* SecondaryFireRight = nullptr;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ParticleSystem = nullptr;

	UPROPERTY(VisibleAnywhere)
		UMyPawnMovementComponent* MyPawnMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		USpawnAnimComponent* SpawnAnimComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UCrossHairComponent* CrossHairComponent = nullptr;

// Primary fire variables
public:

	UPROPERTY(EditDEfaultsOnly, Category=PrimaryFire)
		FColor PrimaryProjectileColor = FColor::Blue;

	UPROPERTY(EditDEfaultsOnly, BlueprintReadWrite, Category = PrimaryFire)
		TSubclassOf<AProjectile> PrimaryProjectileClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = PrimaryFire)
		float PrimaryProyectileRate = 0.2F;

// Secondary fire variables
public:

	UPROPERTY(EditDEfaultsOnly, Category = SecondaryFire)
		FColor SecondaryProjectileColor = FColor::Orange;

	UPROPERTY(EditDEfaultsOnly, BlueprintReadWrite, Category = SecondaryFire)
		TSubclassOf<AProjectile> SecondaryProjectileClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = SecondaryFire)
		float SecondaryProjectileRate = 0.6F;

//Protected variables
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float Health = 0.F;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<AGameModeBase> GameModeClass = nullptr;

	AMyGameModeBase* GameMode = nullptr;

	UMyGameInstance* GameInstance = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* ExplosionParticleSystem = LoadObject<UParticleSystem>(NULL, TEXT("/Game/Assets/Particles/P_Pixel_Explosion_Player.P_Pixel_Explosion_Player"), NULL, LOAD_None, NULL);

	UPROPERTY()
		float DamageValue = 0.1F;

// Public variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bMoveEnabled = false;

	


// Getter functions

public:

	UBoxComponent* GetBoxComponent() { return BoxComponent; }

	UStaticMeshComponent* GetStaticMeshComponent() { return StaticMeshComponent; }

	UMyPawnMovementComponent* GetMyPawnMovementComponent() { return MyPawnMovementComponent; }

	UFireComponent* GetPrimaryFireComponent() { return PrimaryFireSpawn; }

	UFireComponent* GetSecondaryFireComponentLeft() { return SecondaryFireLeft; }

	UFireComponent* GetSecondaryFireComponentRight() { return SecondaryFireRight; }

protected:
		
	UFUNCTION()
		void ReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	//UFUNCTION()
		//void OnEnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnEnemyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
