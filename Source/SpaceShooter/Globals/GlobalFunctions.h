// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Globals/GlobalTypes.h"
#include "GlobalFunctions.generated.h"

class UMySaveGame;
/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UGlobalFunctions : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		static UMySaveGame* SaveGame(int32 InSlot, const FPlayerData& InPlayerData, const FName& InCurrentLevelName);

	UFUNCTION(BlueprintCallable)
		static void LoadGame(int32 InSlot, UObject* InWorldContext);
};
