// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthBar.h"
#include "Widgets/EnemyHealthBarWidget.h"

DEFINE_LOG_CATEGORY(LogGame);

UEnemyHealthBar::UEnemyHealthBar()
{
	SetDrawAtDesiredSize(true);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UEnemyHealthBar::InitWidget()
{
	Super::InitWidget();

	if (Widget)
	{
		if (!Widget->IsA(UEnemyHealthBarWidget::StaticClass()))
		{
			UE_LOG(LogGame, Warning, TEXT("WidgetClass for %s does not derive from EnemyHealthBarWidget"), *GetNameSafe(GetOwner()));
		}

		UEnemyHealthBarWidget* EnemyHealthBarWidget = Cast<UEnemyHealthBarWidget>(Widget);
		if (EnemyHealthBarWidget)
		{
			EnemyHealthBarWidget->SetOwningActor(GetOwner());
		}
	}
}

