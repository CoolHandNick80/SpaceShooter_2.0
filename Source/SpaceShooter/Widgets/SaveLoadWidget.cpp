// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadWidget.h"
#include "GameInstances/MyGameInstance.h"
#include "GameFramework/GameModeBase.h"
#include "GameModes/MainMenu_GameMode.h"
#include "GameModes/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Widgets/MyButton.h"
#include "Widgets/SlotWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"


void USaveLoadWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetupData();
	
	if (BackButton != nullptr)
	{
		BackButton->SetKeyboardFocus();
	}
	
	GenerateSlots();

}

void USaveLoadWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (BackButton != nullptr)
	{
		BackButton->CheckFocus();
	}
}

void USaveLoadWidget::SetupData()
{
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	verify(GameInstance != nullptr);
	
	if(GameInstance != nullptr)
	{
		AmountOfSlots = GameInstance->GetSlotsAmount();
	}


	GameMode = UGameplayStatics::GetGameMode(this);
	verify(GameMode != nullptr);

	if (GameMode != nullptr)
	{
		CheckGameMode(GameMode);
	}

	Text = Cast<UTextBlock>(WidgetTree->FindWidget("TXT_SaveLoad"));
	if (bIsLoading == true)
	{
		Text->SetText(FText::FromString("Choose a slot to load your game"));
	}
	else
	{
		if (bIsLoading == false)
		{
			Text->SetText(FText::FromString("Choose a slot to save your game"));
		}
	}
	
	BackButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_Back"));
	verify(BackButton != nullptr);

	ScrollBox = Cast<UScrollBox>(WidgetTree->FindWidget("SlotBox"));
	verify(ScrollBox != nullptr);
}

void USaveLoadWidget::CheckGameMode(AGameModeBase* InGameMode)
{
	MainMenu_GameMode = Cast<AMainMenu_GameMode>(InGameMode);
	
	MyGameModeBase = Cast<AMyGameModeBase>(InGameMode);

	if (MainMenu_GameMode != nullptr)
	{
		bIsLoading = true;
	}
	else
	{
		if (MyGameModeBase != nullptr)
		{
			bIsLoading = false;
		}
	}
}

void USaveLoadWidget::GenerateSlots()
{
	SlotsArray.Empty();

	ScrollBox->ClearChildren();

	for (int32 Index = 1; Index <= AmountOfSlots; Index++)
	{
		FString SlotName = "MySaveSlot";

		SlotName.Append(FString::FromInt(Index));

		USlotWidget* SaveSlot = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass, FName(*SlotName));
		if (SaveSlot != nullptr)
		{
			SaveSlot->SetSaveLoadWidget(this);
			SaveSlot->SetSlotIndex(Index);
			SlotsArray.Add(SaveSlot);
			ScrollBox->AddChild(SaveSlot);
		}
	}
}


void USaveLoadWidget::Resume()
{
	if (MainMenu_GameMode != nullptr)
	{
		MainMenu_GameMode->ResumeFromSaveLoadMenu();
	}
	else
	{
		if (MyGameModeBase != nullptr)
		{
			MyGameModeBase->ResumeFromSaveLoadMenu();
		}
	}
}

