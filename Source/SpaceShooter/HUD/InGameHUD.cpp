// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

void AInGameHUD::SetupInGameGUI()
{
	if (InGameGUIClass != nullptr)
	{
		InGameGUI = CreateWidget<UUserWidget>(GetWorld(), InGameGUIClass);

		if (InGameGUI != nullptr)
		{
			InGameGUI->AddToViewport();
		}
	}
}

void AInGameHUD::SetupGameOverGUI()
{
	if (GameOverGUIClass != nullptr)
	{
		GameOverGUI = CreateWidget<UUserWidget>(GetWorld(), GameOverGUIClass);

		if (GameOverGUI != nullptr)
		{
			GameOverGUI->AddToViewport();
		}
	}
}

void AInGameHUD::SetupPauseMenuGUI()
{
	if (PauseGUIClass != nullptr)
	{
		PauseGUI = CreateWidget<UUserWidget>(GetWorld(), PauseGUIClass);

		if (PauseGUI != nullptr)
		{
			PauseGUI->AddToViewport();
		}
	}
}

void AInGameHUD::ResumeFromPause()
{
	if (PauseGUI != nullptr)
	{
		PauseGUI->RemoveFromViewport();
	}
}

void AInGameHUD::SetupSaveLoadGUI()
{
	if (SaveLoadGUIClass != nullptr)
	{
		SaveLoadGUI = CreateWidget<UUserWidget>(GetWorld(), SaveLoadGUIClass);

		if (SaveLoadGUI != nullptr)
		{
			SaveLoadGUI->AddToViewport();
		}
	}
}

void AInGameHUD::ResumeFromSaveLoad()
{
	if (SaveLoadGUI != nullptr)
	{
		SaveLoadGUI->RemoveFromViewport();
	}
}
