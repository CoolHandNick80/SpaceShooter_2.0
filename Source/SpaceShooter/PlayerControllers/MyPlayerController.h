// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AMyPawn;
class UMyPawnMovementComponent;
class UFireComponent;
class AMyGameModeBase;

UCLASS()
class SPACESHOOTER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
		AMyPawn* MyPawn = nullptr;
	
	UPROPERTY()
		UMyPawnMovementComponent* MyPawnMovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UFireComponent* PrimaryFireSpawn = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UFireComponent* SecondaryFireLeft = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UFireComponent* SecondaryFireRight = nullptr;

	UPROPERTY(EditDefaultsOnly)
		AMyGameModeBase* GameMode = nullptr;

protected:
	
	virtual void SetupInputComponent() override;
	
	void MoveForward(float Value);

	void MoveRight(float Value);

	void MoveUp(float Value);

	void PrimaryFire();

	void SecondaryFire();

	void EndPrimaryFire();

	void EndSecondaryFire();

	void OpenPauseMenu();

public:

	virtual void OnPossess(APawn* aPawn) override;
};
