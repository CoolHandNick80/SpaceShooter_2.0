// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu_GameMode.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API AMainMenu_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMainMenu_GameMode();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> MyWidgetClass = nullptr;

	UUserWidget* MyWidget = nullptr;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> SaveLoadGUIClass = nullptr;

	UPROPERTY()
		UUserWidget* SaveLoadGUI = nullptr;

public:
	UFUNCTION(BlueprintCallable)
	void SetupSaveLoadGUI();
	
	UFUNCTION(BlueprintCallable)
	void ResumeFromSaveLoadMenu();

	
};
