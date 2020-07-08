// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyGameplayCamera.generated.h"

UCLASS()
class SPACESHOOTER_API AMyGameplayCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyGameplayCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent = nullptr;

	AActor* TargetActor = nullptr;

protected:
	
	void UpdateGameplayCamera();

	

public:
	void SetTargetActor(AActor* InTargetActor) { TargetActor = InTargetActor; }
};
