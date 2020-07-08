// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairWidget.h"

void UCrossHairWidget::NativeConstruct()
{
}

void UCrossHairWidget::SetupData()
{
	
}

void UCrossHairWidget::SetOwningActor(AActor * NewOwner)
{
	if (OwningActor == NewOwner)
	{
		// Skip repeated calls
		return;
	}

	OwningActor = NewOwner;

	//OnOwningActorChanged.Broadcast(NewOwner);
}
