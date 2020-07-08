// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "GameModes/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Widgets/MyButton.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetupData();

	FillArray();

	ResumeButton->SetKeyboardFocus();
}

void UPauseMenuWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (auto& Button : ButtonsArray)
	{
		Button->CheckFocus();
	}
}

void UPauseMenuWidget::SetupData()
{
	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(GameMode != nullptr);
}

void UPauseMenuWidget::FillArray()
{
	ResumeButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_Resume"));

	if (ResumeButton != nullptr)
	{
		ButtonsArray.Add(ResumeButton);
	}

	SaveGameButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_SaveGame"));

	if (SaveGameButton != nullptr)
	{
		ButtonsArray.Add(SaveGameButton);
	}

	ExitButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_Exit"));

	if (ExitButton != nullptr)
	{
		ButtonsArray.Add(ExitButton);
	}

	QuitButton = Cast<UMyButton>(WidgetTree->FindWidget("BTN_Quit"));

	if (QuitButton != nullptr)
	{
		ButtonsArray.Add(QuitButton);
	}

	LastArrayIndex = (ButtonsArray.Num() - 1);
}


