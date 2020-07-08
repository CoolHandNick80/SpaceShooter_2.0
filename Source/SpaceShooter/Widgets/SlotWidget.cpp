// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"
#include "GameInstances/MyGameInstance.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Widgets/MyButton.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/SaveLoadWidget.h"
#include "Globals/GlobalFunctions.h"


void USlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetupData();

	Update();

}

void USlotWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (SaveLoadButton != nullptr)
	{
		SaveLoadButton->CheckFocus();
	}

	
}

void USlotWidget::SetupData()
{
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	verify(GameInstance != nullptr);
	
	SaveLoadButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_SaveLoad"));
	verify(SaveLoadButton != nullptr);

	Canvas = Cast<UCanvasPanel>(WidgetTree->FindWidget("PNL_Canvas"));
	verify(Canvas != nullptr);

	LevelText = Cast<UTextBlock>(WidgetTree->FindWidget("TXT_Level"));
	verify(LevelText != nullptr);

	PointsText = Cast<UTextBlock>(WidgetTree->FindWidget("TXT_Points"));
	verify(PointsText != nullptr);

	MaxHealthText = Cast<UTextBlock>(WidgetTree->FindWidget("TXT_MaxHealth"));
	verify(MaxHealthText != nullptr);

	DateText = Cast<UTextBlock>(WidgetTree->FindWidget("TXT_Date"));
	verify(DateText != nullptr);
	
	HourText = Cast<UTextBlock>(WidgetTree->FindWidget("TXT_Hour"));
	verify(HourText != nullptr);

	MinuteText = Cast<UTextBlock>(WidgetTree->FindWidget("TXT_Minute"));
	verify(MinuteText != nullptr);

	SecondText = Cast<UTextBlock>(WidgetTree->FindWidget("TXT_Second"));
	verify(SecondText != nullptr);
}

void USlotWidget::Update()
{
	FString SlotName = "MySaveSlot";

	SlotName.Append(FString::FromInt(SlotIndex));

	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		SaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (LevelText != nullptr)
		{
			LevelText->SetText(FText::FromName(SaveGame->CurrentLevelName));
		}

		if (PointsText != nullptr)
		{
			PointsText->SetText(FText::AsNumber(SaveGame->SavedPlayerData.Score));
		}

		if (MaxHealthText != nullptr)
		{
			MaxHealthText->SetText(FText::AsNumber(SaveGame->SavedPlayerData.MaxHealth));
		}

		if (DateText != nullptr)
		{
			DateText->SetText(FText::AsDate(SaveGame->SaveDateTime.GetDate()));
		}

		if (HourText != nullptr)
		{
			if (SaveGame->SaveDateTime.GetHour() >= 10)
			{
				HourText->SetText(FText::AsNumber(SaveGame->SaveDateTime.GetHour()));
			}
			else
			{
				HourText->SetText(FText::FromString(FString("0").Append(FString::FromInt(SaveGame->SaveDateTime.GetHour()))));
			}
		}

		if (MinuteText != nullptr)
		{
			if (SaveGame->SaveDateTime.GetMinute() >= 10)
			{
				MinuteText->SetText(FText::AsNumber(SaveGame->SaveDateTime.GetMinute()));

			}
			else
			{
				MinuteText->SetText(FText::FromString(FString("0").Append(FString::FromInt(SaveGame->SaveDateTime.GetMinute()))));
			}
		}
		if (SecondText != nullptr)
		{
			if (SaveGame->SaveDateTime.GetSecond() >= 10)
			{
				SecondText->SetText(FText::AsNumber(SaveGame->SaveDateTime.GetSecond()));
			}
			else
			{
				SecondText->SetText(FText::FromString(FString("0").Append (FString::FromInt(SaveGame->SaveDateTime.GetSecond()))));
			}
		}

		if (SaveLoadButton != nullptr)
		{
			SaveLoadButton->SetIsEnabled(true);
		}

		if (Canvas != nullptr)
		{
			Canvas->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
	else
	{
		if (SaveLoadButton != nullptr)
		{
			SaveLoadButton->SetIsEnabled(!SaveLoadWidget->bIsLoading);
		}
		
		if (Canvas != nullptr)
		{
			Canvas->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void USlotWidget::SaveLoad()
{
	if (SaveLoadWidget->bIsLoading)
	{
		UGlobalFunctions::LoadGame(SlotIndex, this);
	}
	else
	{
		UGlobalFunctions::SaveGame(SlotIndex, GameInstance->GetPlayerData(),FName (*UGameplayStatics::GetCurrentLevelName(this)));
		Update();
	}
}
