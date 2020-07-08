// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Globals/GlobalTypes.h"
#include "Utils/MySaveGame.h"
#include "MyGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreUpdated);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthUpdated);


/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

		virtual void Init() override;

public:

	FOnScoreUpdated OnScoreUpdated;

	FOnHealthUpdated OnHealthUpdated;

protected:

	UPROPERTY()
		UMySaveGame* SaveGame = nullptr;

	UPROPERTY()
		FPlayerData PlayerData;

	UPROPERTY()
		FName CurrentLevelName;

	UPROPERTY()
		bool bIsLoading = false;

	UPROPERTY(VisibleAnywhere)
		int32 AmountOfSlots = 6;


public:

	FPlayerData& GetPlayerData() { return PlayerData; }

	void SetPLayerData(const FPlayerData& InPlayerData) { PlayerData = InPlayerData; }

	void UpdateScore(int32 InNewScore);
	
	void UpdateHealth(float InDamage);

	void SetupHealth();

	void SetCurrentLevel(FName InLevelName) { CurrentLevelName = InLevelName; }

	FName GetCurrentLevel() { return CurrentLevelName; }

	void SetIsLoading(bool InBool) { bIsLoading = InBool; }

	bool GetIsLoading() { return bIsLoading; }

	void SetSaveGame(UMySaveGame* InSaveGame) { SaveGame = InSaveGame; }

	UMySaveGame* GetSaveGame() { return SaveGame; }

	int32 GetSlotsAmount() { return AmountOfSlots; }
};
