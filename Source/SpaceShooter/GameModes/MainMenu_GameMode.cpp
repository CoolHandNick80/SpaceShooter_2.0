// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_GameMode.h"
#include "Kismet/GameplayStatics.h"

AMainMenu_GameMode::AMainMenu_GameMode()
{
	DefaultPawnClass = NULL;
}


void AMainMenu_GameMode::BeginPlay()
{
	if (MyWidgetClass != nullptr)
	{
		MyWidget = CreateWidget<UUserWidget>(GetWorld(), MyWidgetClass);

		MyWidget->AddToViewport();

		APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (MyPlayerController != nullptr)
		{
			MyPlayerController->SetInputMode(FInputModeUIOnly());
			MyPlayerController->bShowMouseCursor = true;
		}
	}
}

void AMainMenu_GameMode::SetupSaveLoadGUI()
{
	if (SaveLoadGUIClass != nullptr)
	{
		SaveLoadGUI = CreateWidget<UUserWidget>(GetWorld(), SaveLoadGUIClass);

		if (SaveLoadGUI != nullptr)
		{
			MyWidget->RemoveFromViewport();
			SaveLoadGUI->AddToViewport();
		}
	}
}

void AMainMenu_GameMode::ResumeFromSaveLoadMenu()
{
	if (SaveLoadGUI != nullptr)
	{
		SaveLoadGUI->RemoveFromViewport();
		MyWidget->AddToViewport();
	}
}
