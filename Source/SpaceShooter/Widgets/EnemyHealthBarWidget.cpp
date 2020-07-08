// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthBarWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Enemies/EnemyBase.h"


void UEnemyHealthBarWidget::NativeConstruct()
{
	SetupData();
}

void UEnemyHealthBarWidget::SetupData()
{
	EnemyHealthProgressBar = Cast<UProgressBar>(WidgetTree->FindWidget("EnemyHealthBar"));
	UpdateHealth();
}

void UEnemyHealthBarWidget::SetOwningActor(AActor * NewOwner)
{
	if (OwningActor == NewOwner)
	{
		// Skip repeated calls
		return;
	}

	OwningActor = NewOwner;

	OnOwningActorChanged.Broadcast(NewOwner);
}

void UEnemyHealthBarWidget::UpdateHealth()
{
	AEnemyBase* MyEnemyOwner = Cast<AEnemyBase>(OwningActor);

	if (MyEnemyOwner)
	{
		EnemyHealthProgressBar->SetPercent(MyEnemyOwner->GetEnemyHealth() / MyEnemyOwner->GetEnemyMaxHealth());
	}
}