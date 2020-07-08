// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/MyGameInstance.h"
#include "PlayerControllers/MyPlayerController.h"
#include "Engine/engine.h"

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetupData();

	SpawnGameplayCamera();

	SpawnInGameGUI();

	SetInputModeGameOnly();

	SetupHealth();
}

void AMyGameModeBase::SpawnGameplayCamera()
{
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (MyPawn != nullptr)
	{
		const FVector& PawnLocation = MyPawn->GetActorLocation();

		GameplayCamera = GetWorld()->SpawnActor<AMyGameplayCamera>(GameplayCameraClass, PawnLocation + (FVector::ForwardVector * 60), FRotator::ZeroRotator);

		if (GameplayCamera != nullptr)
		{
			GameplayCamera->SetTargetActor(MyPawn);

			

			if (PlayerController != nullptr)
			{
				PlayerController->SetViewTarget(GameplayCamera);
			}
		}
	}
}

void AMyGameModeBase::SpawnInGameGUI()
{
	

	if (PlayerController != nullptr)
	{
		

		if (InGameHUD != nullptr)
		{
			InGameHUD->SetupInGameGUI();
		}
	}
}

void AMyGameModeBase::SetInputModeGameOnly()
{
	

	if (PlayerController != nullptr)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void AMyGameModeBase::SetInputModeUIOnly()
{
	

	if (PlayerController != nullptr)
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
	}
}

void AMyGameModeBase::SetupHealth()
{
	

	if (GameInstance != nullptr)
	{
		GameInstance->SetupHealth();
		GameInstance->UpdateHealth(0);
	}
}

void AMyGameModeBase::SetupData()
{
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	verify(GameInstance != nullptr);
	
	PlayerController = Cast<AMyPlayerController> (UGameplayStatics::GetPlayerController(this, 0));
	verify(PlayerController != nullptr);
	
	if (PlayerController != nullptr)
	{
		InGameHUD = Cast<AInGameHUD>(PlayerController->GetHUD());
		verify(InGameHUD != nullptr);
	}

	if (GameInstance != nullptr)
	{
		GameInstance->SetCurrentLevel(FName(*UGameplayStatics::GetCurrentLevelName(GetWorld(),true)));
	}
}

void AMyGameModeBase::OpenPauseMenu()
{
	if (PlayerController != nullptr)
	{
		if (InGameHUD != nullptr)
		{
			UGameplayStatics::SetGamePaused(GetWorld(), true);
			InGameHUD->SetupPauseMenuGUI();
			PlayerController->bShowMouseCursor = true;
			SetInputModeUIOnly();
		}
	}
}

void AMyGameModeBase::Resume()
{
	if (PlayerController != nullptr)
	{
		if (InGameHUD != nullptr)
		{
			UGameplayStatics::SetGamePaused(GetWorld(), false);
			InGameHUD->ResumeFromPause();
			PlayerController->bShowMouseCursor = false;
			SetInputModeGameOnly();
		}
	}
}

void AMyGameModeBase::OpenSaveLoadMenu()
{
	if (InGameHUD != nullptr)
	{
		InGameHUD->ResumeFromPause();
		InGameHUD->SetupSaveLoadGUI();
	}
}

void AMyGameModeBase::ResumeFromSaveLoadMenu()
{
	InGameHUD->ResumeFromSaveLoad();
	InGameHUD->SetupPauseMenuGUI();
}

void AMyGameModeBase::PlayCamShake(TSubclassOf<class UCameraShake> InShake, FVector InEpicenter)
{
	UGameplayStatics::PlayWorldCameraShake(this, InShake, InEpicenter, NULL, NULL);
}

void AMyGameModeBase::UpdateEnemyCount(int32 InVal)
{
	EnemyCount += InVal;
}

void AMyGameModeBase::EnemyKilled()
{
	EnemiesKilled++;
	UpdateEnemyCount(-1);

	//GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (GameInstance != nullptr)
	{
		GameInstance->UpdateScore(EnemyScoreValue);
	}
}

void AMyGameModeBase::GameOver()
{
	//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController != nullptr)
	{
		//InGameHUD = Cast<AInGameHUD>(PlayerController->GetHUD());

		if (InGameHUD != nullptr)
		{
			InGameHUD->SetupGameOverGUI();
			PlayerController->bShowMouseCursor = true;
			SetInputModeUIOnly();
		}
	}
}