// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Utils/MySaveGame.h"
#include "SlotWidget.generated.h"

class UMyButton;
class UCanvasPanel;
class UTextBlock;
class USaveLoadWidget;
class UMyGameInstance;



/**
 * 
 */
UCLASS()
class SPACESHOOTER_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry & MyGeometry, float InDeltaTime) override;

protected:

	UPROPERTY()
		UMyGameInstance* GameInstance = nullptr;
	
	UPROPERTY()
		UMyButton* SaveLoadButton = nullptr;

	UPROPERTY()
		UCanvasPanel* Canvas = nullptr;

	UPROPERTY()
		UTextBlock* LevelText = nullptr;

	UPROPERTY()
		UTextBlock* PointsText = nullptr;

	UPROPERTY()
		UTextBlock* MaxHealthText = nullptr;

	UPROPERTY()
		UTextBlock* DateText = nullptr;

	UPROPERTY()
		UTextBlock* HourText = nullptr;

	UPROPERTY()
		UTextBlock* MinuteText = nullptr;

	UPROPERTY()
		UTextBlock* SecondText = nullptr;


	UPROPERTY()
		int32 SlotIndex = 0;

	UPROPERTY()
		USaveLoadWidget* SaveLoadWidget = nullptr;

	UPROPERTY()
		UMySaveGame* SaveGame = nullptr;

protected:

	void SetupData();

	void Update();

public:

	void SetSaveLoadWidget(USaveLoadWidget* InSaveLoadWidget) { SaveLoadWidget = InSaveLoadWidget; }

	void SetSlotIndex(int32 InIndex) { SlotIndex = InIndex; }

	UFUNCTION(BlueprintCallable)
		void SaveLoad();	
};
