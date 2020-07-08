// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	PlayerData = FPlayerData();
	if (PlayerData.MaxHealth == 0.F)
	{
		PlayerData.MaxHealth = 100.F;
	}

	PlayerData.Health = PlayerData.MaxHealth;
	
}

void UMyGameInstance::UpdateScore(int32 InNewScore)
{
	PlayerData.Score += InNewScore;

	OnScoreUpdated.Broadcast();

	if (PlayerData.Score > PlayerData.TopScore)
	{
		PlayerData.TopScore = PlayerData.Score;
	}
}

void UMyGameInstance::UpdateHealth(float InDamage)
{
	PlayerData.Health -= InDamage;

	OnHealthUpdated.Broadcast();
}

void UMyGameInstance::SetupHealth()
{
	PlayerData.Health = PlayerData.MaxHealth;
}
