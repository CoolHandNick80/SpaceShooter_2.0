// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UMyGameInstance;
class AMainMenu_GameMode;
class UMyButton;

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;
	
protected:

	UPROPERTY()
		UMyGameInstance* GameInstance = nullptr;

	UPROPERTY(BlueprintReadOnly)
		AMainMenu_GameMode* GameMode = nullptr;

	UPROPERTY()
		int32 LastArrayIndex = 0;

	UPROPERTY()
		TArray<UMyButton*> ButtonsArray;
	
	UPROPERTY()
		UMyButton* NewGameButton = nullptr;

	UPROPERTY()
		UMyButton* ContinueButton = nullptr;

	UPROPERTY()
		UMyButton* LoadGameButton = nullptr;

	UPROPERTY()
		UMyButton* QuitButton = nullptr;

	UPROPERTY()
		int32 AmountOfSlots = 6;

	UPROPERTY()
		TArray<int32> IndexArray;
 
protected:

	void SetupData();

	bool CheckSaveGame(int32 InSlotIndex);

	void FillArray(int32 InSlotIndex);

	void OrderArray();
	
	UFUNCTION(BlueprintCallable)
	void Continue();


};
