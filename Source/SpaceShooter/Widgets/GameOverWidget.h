
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UMyGameInstance;
class UMyButton;

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UGameOverWidget : public UUserWidget
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
		UMyButton* RetryButton = nullptr;

	UPROPERTY()
		UMyButton* QuitButton = nullptr;
	

	UPROPERTY()
		UMyGameInstance* GameInstance = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
		FName CurrentLevelName;

protected:

	void SetupData();

	void FillArray();

	
};
