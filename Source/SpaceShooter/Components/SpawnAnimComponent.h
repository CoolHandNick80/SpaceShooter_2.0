// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "SpawnAnimComponent.generated.h"

class AMyPawn;
class AMyGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API USpawnAnimComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnAnimComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	float Pitch = 0.F;

	float Roll = 0.F;

	AMyPawn* MyPawn = nullptr;

	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
		UCurveFloat* CurveFloat = nullptr;

	AMyGameModeBase* GameMode = nullptr;

	FVector SpawnLocation = FVector::ZeroVector;

	
private:

	FTimeline SpawnAnimation;

	FRotator ActorRotation = FRotator::ZeroRotator;

private:
	
	UFUNCTION()
		void HandleProgress(float Value);

	UFUNCTION()
		void EnableMovement();


	void SetupData();

public:

	UFUNCTION()
		void PlayAnimation();
};
