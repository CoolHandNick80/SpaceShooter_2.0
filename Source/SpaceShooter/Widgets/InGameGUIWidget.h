// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Globals/GlobalTypes.h"
#include "Components/ProgressBar.h"
#include "InGameGUIWidget.generated.h"

class UTextBlock;
class UMyGameInstance;

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UInGameGUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
		virtual void NativeConstruct() override;

protected:

	UPROPERTY()
		UTextBlock* ScoreTextBlock = nullptr;

	UPROPERTY()
		UProgressBar* HealthProgressBar = nullptr;

	UPROPERTY()
		UMyGameInstance* GameInstance = nullptr;

protected:

	void SetupData();

	UFUNCTION()
		void UpdateScore();

	UFUNCTION()
		void UpdateHealth();
};
