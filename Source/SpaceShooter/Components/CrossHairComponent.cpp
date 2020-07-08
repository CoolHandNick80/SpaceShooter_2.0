// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairComponent.h"
#include "Widgets/CrossHairWidget.h"

UCrossHairComponent::UCrossHairComponent()
{
	SetDrawAtDesiredSize(true);
	SetWidgetSpace(EWidgetSpace::Screen);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCrossHairComponent::InitWidget()
{
	Super::InitWidget();

	if (Widget)
	{
		/*if (!Widget->IsA(UCrossHairWidget::StaticClass()))
		{
			UE_LOG(LogGame, Warning, TEXT("WidgetClass for %s does not derive from EnemyHealthBarWidget"), *GetNameSafe(GetOwner()));
		}*/

		UCrossHairWidget* CrossHairWidget = Cast<UCrossHairWidget>(Widget);
		if (CrossHairWidget)
		{
			CrossHairWidget->SetOwningActor(GetOwner());
		}
	}
}
