// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "EnemyFireComponent.generated.h"

class AMyPawn;
class AProjectile;
class AEnemyBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UEnemyFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	AMyPawn* MyPawn = nullptr;

	AEnemyBase* MyOwner = nullptr;

	UPROPERTY()
		FTimerHandle FireTimerHandle;

	bool bIsInRange = false;

	

	float RateOfFire = 0.4F;

public:

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<AProjectile> ProjectileClass = nullptr;

	UPROPERTY(VisibleAnywhere)
		FColor ProjectileColor = FColor::White;

protected:

	void SetupData();

	float GetDistanceFromPlayer();

	void CheckDistance();
	
	UFUNCTION()
	void Fire();
	
public:

	void StartTimer();

	void StopTimer();
		
};
