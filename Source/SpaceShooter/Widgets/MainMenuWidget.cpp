// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "GameInstances/MyGameInstance.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Widgets/MyButton.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/MainMenu_GameMode.h"
#include "Globals/GlobalFunctions.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameMode = Cast<AMainMenu_GameMode>(UGameplayStatics::GetGameMode(this));
	verify(GameMode != nullptr);

	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	verify(GameInstance != nullptr);

	if (GameInstance != nullptr)
	{
		AmountOfSlots = GameInstance->GetSlotsAmount();
	}
	
	SetupData();

	if (CheckSaveGame(AmountOfSlots))
	{
		ContinueButton->SetKeyboardFocus();
	}
	else
	{
		NewGameButton->SetKeyboardFocus();
		ContinueButton->SetIsEnabled(false);
		LoadGameButton->SetIsEnabled(false);
	}
}

void UMainMenuWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (auto& Button : ButtonsArray)
	{
		Button->CheckFocus();
	}
}

void UMainMenuWidget::SetupData()
{
	NewGameButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_NewGame"));
	
	if (NewGameButton != nullptr)
	{
		ButtonsArray.Add(NewGameButton);
	}

	ContinueButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_Continue"));

	if (ContinueButton != nullptr)
	{
		ButtonsArray.Add(ContinueButton);
	}

	LoadGameButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_LoadGame"));

	if (LoadGameButton != nullptr)
	{
		ButtonsArray.Add(LoadGameButton);
	}

	QuitButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_Quit"));

	if (QuitButton != nullptr)
	{
		ButtonsArray.Add(QuitButton);
	}

	LastArrayIndex  = (ButtonsArray.Num()-1);
}

bool UMainMenuWidget::CheckSaveGame(int32 InSlotIndex)
{
	if (InSlotIndex == 0)
	{
		return false;
	}
	else
	{
		FString SlotName = "MySaveSlot";

		SlotName.Append(FString::FromInt(InSlotIndex));

		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			return true;
		}
		else
		{
			return CheckSaveGame(InSlotIndex - 1);
		}
	}
}

void UMainMenuWidget::FillArray(int32 InSlotIndex)
{
	for (int32 i = 1; i <= InSlotIndex; i++)
	{
		FString SlotName = "MySaveSlot";

		SlotName.Append(FString::FromInt(i));

		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			//UMySaveGame* SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

			//SaveGameObject = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

			IndexArray.Add(i);
		}
	}
}

void UMainMenuWidget::OrderArray()
{
	UMySaveGame* CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	UMySaveGame* NextSaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));


	for (int32 i = 0; i < IndexArray.Num(); i++)
	{
		for (int32 j = i + 1; j != IndexArray.Num(); j++)
		{
			FString CurrentSlotName = "MySaveSlot";

			CurrentSlotName.Append(FString::FromInt(IndexArray[i]));

			CurrentSaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentSlotName, 0));

			FString NextSlotName = "MySaveSlot";

			NextSlotName.Append(FString::FromInt(IndexArray[j]));

			NextSaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentSlotName, 0));

			if (CurrentSaveGame->SaveDateTime < NextSaveGame->SaveDateTime)
			{
				int32 Temp = IndexArray[i];
				IndexArray[i] = IndexArray[j];
				IndexArray[j] = Temp;
			}

		}
	}
}

void UMainMenuWidget::Continue()
{
	FillArray(AmountOfSlots);
	OrderArray();
	UGlobalFunctions::LoadGame(IndexArray[0], this);
	
}



