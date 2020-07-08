// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameGUIWidget.h"
#include "GameInstances/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Engine/Engine.h"


void UInGameGUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetupData();
}

void UInGameGUIWidget::SetupData()
{
	ScoreTextBlock = Cast<UTextBlock>(WidgetTree->FindWidget("ScoreText"));
	
	HealthProgressBar = Cast<UProgressBar>(WidgetTree->FindWidget("Health"));

	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (GameInstance != nullptr)
	{
		GameInstance->OnScoreUpdated.AddDynamic(this, &UInGameGUIWidget::UpdateScore);
		GameInstance->OnHealthUpdated.AddDynamic(this, &UInGameGUIWidget::UpdateHealth);
		//UpdateHealth();
		UpdateScore();
	}
}

void UInGameGUIWidget::UpdateScore()
{
	if (GameInstance != nullptr)
	{
		FString ScoreString = FString::FromInt(GameInstance->GetPlayerData().Score);

		FText ScoreText = FText::FromString(ScoreString);

		ScoreTextBlock->SetText(ScoreText);
	}
}

void UInGameGUIWidget::UpdateHealth()
{
	if (GameInstance != nullptr)
	{
		HealthProgressBar->SetPercent(GameInstance->GetPlayerData().Health / GameInstance->GetPlayerData().MaxHealth);

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(GameInstance->GetPlayerData()->Health / GameInstance->GetPlayerData()->MaxHealth));
	}
}
