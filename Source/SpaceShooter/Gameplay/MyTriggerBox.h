// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameModes/MyGameModeBase.h"
#include "Enemies/EnemyBase.h"
#include "Enemies/Asteroid.h"
#include "TimerManager.h"
#include "MyTriggerBox.generated.h"



/**
 * 
 */
UCLASS()
class SPACESHOOTER_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


// Variables
protected:
	
	AMyGameModeBase* GameMode = nullptr;

	UPROPERTY()
		FTimerHandle SpawnEnemiesTimerHandle;

	int32 CurrentEnemiesKilled = 0;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AEnemyBase> EnemyOneClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AEnemyBase> EnemyTwoClass = nullptr;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AAsteroid> AsteroidClass = nullptr;

// Functions
protected:

	UFUNCTION()
		void SpawnFunction(UClass* InClass);

	void SpawnFunction(UClass* InClass, float InDelay);


	void StartTimer();

	UFUNCTION()
		void UpdateTimer();

	void StopTimer();

	FVector GetRandomLocation();

};
