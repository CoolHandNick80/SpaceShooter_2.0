// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "Gameplay/Track.h"
#include "Components/BoxComponent.h"
#include "MyPawnMovementComponent.generated.h"

class AMyPawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UMyPawnMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyPawnMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	AMyPawn* MyPawn = nullptr;

	UBoxComponent* BoxComponent = nullptr;

	UStaticMeshComponent* StaticMeshComponent = nullptr;

	float Roll = 0.F;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float DeltaSeconds = 0.F;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float HozSpeed = 0.F;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float VertSpeed = 0.F;

	UPROPERTY(EditDefaultsOnly)
		float ForwardSpeed = 0.F;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float MovementSpeed = 6.F;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float CurrentSpeed = 0.F;

	UPROPERTY(EditAnywhere)
		UCurveFloat* CurveFloat = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration = 1.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UImin = "0.0", UImax = "1.0"))
		float PawnStartOffset = 0.F;

	FVector LastInput = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxForwardDistance = 120.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHorizontalDistance = 320.F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxVerticalDistance = 60.F;

	// Spline movement variables (TEST)
	
	FVector LastSplineLocation = FVector::ZeroVector;

	FVector NewSplineLocation = FVector::ZeroVector;

	FVector DiffVector = FVector::ZeroVector;

	FRotator LastSplineRotation = FRotator::ZeroRotator;

	FRotator NewSplineRotation = FRotator::ZeroRotator;

	FRotator DiffRotator = FRotator::ZeroRotator;



public:
	UPROPERTY(EditAnywhere)
		ATrack* Track = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATrack> MyTrackClass = nullptr;

private:

	FTimeline PawnMover;

protected:

	void SetupData();

public:

	void SetHorizontalInput(float amount);

	void SetForwardInput(float amount);

	void SetVerticalInput(float amount);

	void SetHorizontalSpeed(float Val);

	void SetForwardSpeed(float Val);

	void SetVerticalSpeed(float Val);

	void Move(float InHozSpeed, float InForwardSpeed, float InVerticalSpeed);

	void MoveSpline(float InHozSpeed, float InForwardSpeed, float InVerticalSpeed);

	float SetSpeed(float Speed, float Value);

	UFUNCTION()
		void StartTrack();

private:

	UFUNCTION()
		void HandleProgress(float Value);

	UFUNCTION()
		void EndTrack();


		
};
