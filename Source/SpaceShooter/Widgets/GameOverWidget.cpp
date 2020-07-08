// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/MyGameInstance.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Widgets/MyButton.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetupData();

	FillArray();

	RetryButton->SetKeyboardFocus();
}

void UGameOverWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (auto& Button : ButtonsArray)
	{
		Button->CheckFocus();
	}

}

void UGameOverWidget::SetupData()
{
	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (GameInstance != nullptr)
	{
		CurrentLevelName = GameInstance->GetCurrentLevel();
	}
	
}

void UGameOverWidget::FillArray()
{
	RetryButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_Retry"));

	if (RetryButton != nullptr)
	{
		ButtonsArray.Add(RetryButton);
	}

	QuitButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_Quit"));

	if (QuitButton != nullptr)
	{
		ButtonsArray.Add(QuitButton);
	}

	LastArrayIndex = (ButtonsArray.Num() - 1);

}
