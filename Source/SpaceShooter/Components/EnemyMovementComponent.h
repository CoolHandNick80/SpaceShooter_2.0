// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMovementComponent.generated.h"

class AEnemyBase;
class AGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UEnemyMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	AEnemyBase* MyEnemy = nullptr;

	AGameModeBase* GameMode = nullptr;
	
public:
	
	bool bMoveDirection = false;
	
	UPROPERTY(EditAnywhere)
		float MovementSpeed = 0.F;

	UPROPERTY(EditAnywhere)
		float MinSpeed = 0.F;

	UPROPERTY(EditAnywhere)
		float MaxSpeed = 0.F;

	UPROPERTY(EditAnywhere)
		float DistanceFromPlayer = 0.F;

protected:

	void SetupData();

	void EnemyMovement(float DeltaSeconds);
		
};
