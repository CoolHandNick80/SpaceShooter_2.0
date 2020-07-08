// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> InGameGUIClass = nullptr;

	UPROPERTY()
		UUserWidget* InGameGUI = nullptr;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> GameOverGUIClass = nullptr;

	UPROPERTY()
		UUserWidget* GameOverGUI = nullptr;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> PauseGUIClass = nullptr;

	UPROPERTY()
		UUserWidget* PauseGUI = nullptr;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> SaveLoadGUIClass = nullptr;

	UPROPERTY()
		UUserWidget* SaveLoadGUI = nullptr;

public:

	void SetupInGameGUI();

	void SetupGameOverGUI();

	void SetupPauseMenuGUI();

	void ResumeFromPause();

	void SetupSaveLoadGUI();

	void ResumeFromSaveLoad();

	
};
