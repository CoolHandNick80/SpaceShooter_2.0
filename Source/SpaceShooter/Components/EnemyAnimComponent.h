// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "EnemyAnimComponent.generated.h"

class AEnemyBase;
class AGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UEnemyAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyAnimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	AEnemyBase* MyEnemy = nullptr;

	AGameModeBase* GameMode = nullptr;

	UPROPERTY(EditAnywhere)
		UCurveFloat* EnemyCurve = nullptr;

	UPROPERTY(EditAnywhere)
		FVector SpawnLocation = FVector::ZeroVector;

	FVector SpawnForwardVector = FVector::ZeroVector;

	FTimeline SpawnAnimation;

private:
	UFUNCTION()
		void HandleProgress(float Value);

	void SetupData();

	UFUNCTION()
		void EnableMovement();


public:

	UFUNCTION()
		void PlayAnimation();

};
