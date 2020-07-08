// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveLoadWidget.generated.h"

class UMyGameInstance;
class AMainMenu_GameMode;
class AMyGameModeBase;
class AGameModeBase;
class USlotWidget;
class UMyButton;
class UScrollBox;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API USaveLoadWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;

protected:

	UPROPERTY()
		UMyGameInstance* GameInstance = nullptr;

	UPROPERTY(BlueprintReadOnly)
		AGameModeBase* GameMode = nullptr;

	UPROPERTY(BlueprintReadOnly)
		AMainMenu_GameMode* MainMenu_GameMode = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
		AMyGameModeBase* MyGameModeBase = nullptr;

	UPROPERTY()
		UTextBlock* Text = nullptr;

	UPROPERTY()
		UMyButton* BackButton = nullptr;

	UPROPERTY()
		UScrollBox* ScrollBox = nullptr;

	UPROPERTY()
		int32 AmountOfSlots = 6;
	
	UPROPERTY()
		TArray<USlotWidget*> SlotsArray;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<USlotWidget> SlotWidgetClass = nullptr;

public:

	UPROPERTY()
		bool bIsLoading = false;

protected:

	void SetupData();

	void CheckGameMode(AGameModeBase* InGameMode);

	void GenerateSlots();

public:
	
	UFUNCTION(BlueprintCallable)
		void Resume();	
};
