// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalTypes.generated.h"

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 TopScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MaxHealth;

	//Default ctor
	FPlayerData()
	{
		Score = 0;
		TopScore = 0;
		Health = 0.F;
		MaxHealth = 0.F;
	}

};

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UGlobalTypes : public UObject
{
	GENERATED_BODY()
	
};
