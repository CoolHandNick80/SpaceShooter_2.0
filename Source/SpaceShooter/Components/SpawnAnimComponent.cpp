// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnAnimComponent.h"
#include "Pawns/MyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/MyGameModeBase.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
USpawnAnimComponent::USpawnAnimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupData();	
}


// Called every frame
void USpawnAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SpawnAnimation.TickTimeline(DeltaTime);
}

void USpawnAnimComponent::HandleProgress(float Value)
{
	if (MyPawn != nullptr)
	{
		float NewRoll = FMath::Lerp(Roll, (Roll + 1440.F), Value);

		FRotator NewRotation(ActorRotation.Pitch, ActorRotation.Yaw, NewRoll);
		if (StaticMeshComponent != nullptr)
		{
			StaticMeshComponent->SetRelativeRotation(NewRotation);
		}


		//FVector NewLocation = FMath::Lerp(SpawnLocation, SpawnLocation + (FVector::ForwardVector * 60), Value);

		if (MyPawnMovementComponent != nullptr)
		{
			ATrack* MyTrack = MyPawnMovementComponent->GetMovementTrack();
			if (MyTrack != nullptr)
			{
				USplineComponent* SplineComponent = MyTrack->GetSplineComponent();
				if (SplineComponent != nullptr)
				{
					FVector NewLocation = FMath::Lerp(SpawnLocation, SplineComponent->GetLocationAtDistanceAlongSpline(0.F, ESplineCoordinateSpace::World), Value);

					MyPawn->SetActorLocation(NewLocation);

				}
				
			}

		}

	}
	
}

void USpawnAnimComponent::EnableMovement()
{
	if (MyPawn != nullptr)
	{
		MyPawn->bMoveEnabled = true;

		if (MyPawnMovementComponent != nullptr)
		{
			MyPawnMovementComponent->StartTrack();
		}
	}
}

//Sets Values for Spawning Animation

void USpawnAnimComponent::SetupData()
{
	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (GameMode != nullptr)
	{

		if (CurveFloat != nullptr)
		{
			//bind progress function

			FOnTimelineFloat ProgressFunction;

			ProgressFunction.BindUFunction(this, "HandleProgress");

			SpawnAnimation.AddInterpFloat(CurveFloat, ProgressFunction);

			//bind end function

			FOnTimelineEvent EndFunction;

			EndFunction.BindUFunction(this, "EnableMovement");

			SpawnAnimation.SetTimelineFinishedFunc(EndFunction);

			// Setup variables

			MyPawn = Cast<AMyPawn>(GetOwner());
			verify(MyPawn != nullptr);
			
			if (MyPawn != nullptr)
			{
				StaticMeshComponent = MyPawn->GetStaticMeshComponent();
				MyPawnMovementComponent = MyPawn->GetMyPawnMovementComponent();
				SpawnLocation = MyPawn->GetActorLocation();
				
				if (StaticMeshComponent != nullptr)
				{
					ActorRotation = StaticMeshComponent->GetComponentRotation();

					Pitch = ActorRotation.Pitch;

					Roll = ActorRotation.Roll;
				}
			}
		}
	}
}

void USpawnAnimComponent::PlayAnimation()
{
	SpawnAnimation.PlayFromStart();
}

