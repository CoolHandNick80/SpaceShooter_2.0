// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBar.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGame, Log, All);

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UEnemyHealthBar : public UWidgetComponent
{
	GENERATED_BODY()

		UEnemyHealthBar();

protected:

	virtual void InitWidget() override;

	
	
};
