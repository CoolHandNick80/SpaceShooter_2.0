// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "EnemyHealthBarWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOwningActorChanged, AActor*, NewOwner);

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UEnemyHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual void NativeConstruct() override;

protected:

	UPROPERTY()
		AActor* OwningActor;

	UPROPERTY()
		UProgressBar* EnemyHealthProgressBar = nullptr;

public:

	UPROPERTY()
		FOnOwningActorChanged OnOwningActorChanged;
	

protected:

	void SetupData();

	
public:
	UFUNCTION()
		void SetOwningActor(AActor* NewOwner);

	
	UFUNCTION()
		void UpdateHealth();
	
};
