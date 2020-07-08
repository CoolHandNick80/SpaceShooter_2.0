// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class AMyGameModeBase;
class UMyButton;

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
		
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;

protected:

	

	UPROPERTY()
		int32 LastArrayIndex = 0;

	UPROPERTY()
		TArray<UMyButton*> ButtonsArray;

	UPROPERTY()
		UMyButton* ResumeButton = nullptr;

	UPROPERTY()
		UMyButton* SaveGameButton = nullptr;

	UPROPERTY()
		UMyButton* ExitButton = nullptr;

	UPROPERTY()
		UMyButton* QuitButton = nullptr;
	

protected:

	UPROPERTY(BlueprintReadOnly)
		AMyGameModeBase* GameMode = nullptr;

protected:

	void SetupData();

	void FillArray();

public:

	
	
};
