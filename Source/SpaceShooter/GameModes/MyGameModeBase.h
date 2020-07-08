// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Cameras/MyGameplayCamera.h"
#include "HUD/InGameHUD.h"
#include "MyGameModeBase.generated.h"

class UMyGameInstance;
class AMyPlayerController;


/**
 * 
 */
UCLASS()
class SPACESHOOTER_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Transitions to calls BeginPlay on actors
	virtual void StartPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AMyGameplayCamera> GameplayCameraClass = nullptr;

	UPROPERTY()
		AMyGameplayCamera* GameplayCamera = nullptr;

	UPROPERTY()
		AInGameHUD* InGameHUD = nullptr;

	UPROPERTY()
		UMyGameInstance* GameInstance = nullptr;

	UPROPERTY()
		AMyPlayerController* PlayerController = nullptr;

protected:
	void SpawnGameplayCamera();

	void SpawnInGameGUI();

	void SetInputModeGameOnly();

	void SetInputModeUIOnly();

	void SetupHealth();

	void SetupData();

	
	
public:

	UFUNCTION()
		void UpdateEnemyCount(int32 InVal);

	UFUNCTION()
		void EnemyKilled();

	UFUNCTION()
		void GameOver();

	UFUNCTION()
		void PlayCamShake(TSubclassOf<class UCameraShake> InShake, FVector InEpicenter);

	UFUNCTION()
		void OpenPauseMenu();

	UFUNCTION(BlueprintCallable)
		void Resume();

	UFUNCTION(BlueprintCallable)
		void OpenSaveLoadMenu();

	UFUNCTION(BlueprintCallable)
		void ResumeFromSaveLoadMenu();

protected:

	int32 EnemyCount = 0;
	
	int32 MaxEnemies = 5;

	int32 EnemiesKilled = 0;

	int32 EnemyScoreValue = 5;

public:

	int32 GetEnemiesKilled() { return EnemiesKilled; }

	int32 GetMaxEnemies() { return MaxEnemies; }

	int32 GetEnemyCount() { return EnemyCount; }
	
};