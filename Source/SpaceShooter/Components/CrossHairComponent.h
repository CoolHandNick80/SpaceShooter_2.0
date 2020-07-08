// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "CrossHairComponent.generated.h"


/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UCrossHairComponent : public UWidgetComponent
{
	GENERATED_BODY()

		UCrossHairComponent();

protected:

	virtual void InitWidget() override;
	
};
