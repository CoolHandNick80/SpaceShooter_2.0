// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h "
#include "FireComponent.generated.h"

class AMyPawn;
class AProjectile;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UFireComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//Variables
protected:

	AMyPawn* MyPawn = nullptr;

	UPROPERTY()
		FTimerHandle FireTimerHandle;
	
	bool bFirePressed = false;

	bool bIsFiring = false;

public:
	
	UPROPERTY(VisibleAnywhere)
		TSubclassOf<AProjectile> ProjectileClass = nullptr;
	
	UPROPERTY(VisibleAnywhere)
		FColor ProjectileColor = FColor::White;
	
	UPROPERTY(VisibleAnywhere)
		float RateOfFire = 0.F;
	
//Functions
protected:

	void Fire();

public:

	void StartTimer();

	UFUNCTION()
		void UpdateTimer();

	void StopTimer();
};
