// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Globals/GlobalTypes.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere)
		FPlayerData SavedPlayerData;

	UPROPERTY(VisibleAnywhere)
		FName CurrentLevelName;

	UPROPERTY(VisibleAnywhere)
		FDateTime SaveDateTime = 0;
};
