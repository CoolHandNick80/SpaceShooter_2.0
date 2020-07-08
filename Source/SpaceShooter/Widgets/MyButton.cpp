// Fill out your copyright notice in the Description page of Project Settings.


#include "MyButton.h"

UMyButton::UMyButton(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	
}

void UMyButton::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(ButtonTimerHandle, this, &UMyButton::CheckFocus, 0.1F, true);
}

void UMyButton::CheckFocus()
{
	if (IsHovered())
	{
		SetKeyboardFocus();
		SetMouseStyle();
	}
	else
	{
		if (HasKeyboardFocus())
		{
			SetKeySelected();
		}
		else
		{
			SetKeyNotSelected();
		}
	}

}
