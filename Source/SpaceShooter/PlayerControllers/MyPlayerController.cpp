// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Pawns/MyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/MyGameModeBase.h"



void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);

	InputComponent->BindAxis("MoveUP", this, &AMyPlayerController::MoveUp);

	InputComponent->BindAction("PrimaryFire", IE_Pressed, this, &AMyPlayerController::PrimaryFire);

	InputComponent->BindAction("PrimaryFire", IE_Released, this, &AMyPlayerController::EndPrimaryFire);

	InputComponent->BindAction("SecondaryFire", IE_Pressed, this, &AMyPlayerController::SecondaryFire);

	InputComponent->BindAction("SecondaryFire", IE_Released, this, &AMyPlayerController::EndSecondaryFire);

	InputComponent->BindAction("Pause", IE_Pressed, this, &AMyPlayerController::OpenPauseMenu);

}

void AMyPlayerController::MoveForward(float Value)
{
	if (MyPawn != nullptr)
	{
		MyPawnMovementComponent->SetForwardInput(Value);
	}
}

void AMyPlayerController::MoveRight(float Value)
{
	if (MyPawn != nullptr)
	{
		MyPawnMovementComponent->SetHorizontalInput(Value);
	}
}

void AMyPlayerController::MoveUp(float Value)
{
	if (MyPawn != nullptr)
	{
		MyPawnMovementComponent->SetVerticalInput(Value);
	}
}

void AMyPlayerController::PrimaryFire()
{
	if (MyPawn != nullptr)
	{
		PrimaryFireSpawn->StartTimer();
	}
}

void AMyPlayerController::SecondaryFire()
{
	SecondaryFireLeft->StartTimer();
	SecondaryFireRight->StartTimer();

}

void AMyPlayerController::EndPrimaryFire()
{
	if (MyPawn != nullptr)
	{
		PrimaryFireSpawn->StopTimer();
	}
}

void AMyPlayerController::EndSecondaryFire()
{
	if (MyPawn != nullptr)
	{
		SecondaryFireLeft->StopTimer();
		SecondaryFireRight->StopTimer();
	}
}

void AMyPlayerController::OpenPauseMenu()
{
	GameMode->OpenPauseMenu();
}

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	MyPawn = Cast<AMyPawn>(aPawn);
	MyPawnMovementComponent = MyPawn->GetMyPawnMovementComponent();
	PrimaryFireSpawn = MyPawn->GetPrimaryFireComponent();
	SecondaryFireLeft = MyPawn->GetSecondaryFireComponentLeft();
	SecondaryFireRight = MyPawn->GetSecondaryFireComponentRight();

	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(GameMode != nullptr);
}
