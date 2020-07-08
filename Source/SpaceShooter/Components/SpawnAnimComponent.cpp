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
	float NewRoll = FMath::Lerp(Roll, (Roll + 1440.F), Value);

	FRotator NewRotation(ActorRotation.Pitch, ActorRotation.Yaw, NewRoll);

	StaticMeshComponent->SetRelativeRotation(NewRotation);

	FVector NewLocation = FMath::Lerp(SpawnLocation, SpawnLocation + (FVector::ForwardVector * 60), Value);
	MyPawn->SetActorLocation(NewLocation);
}

void USpawnAnimComponent::EnableMovement()
{
	MyPawn->bMoveEnabled = true;
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

			StaticMeshComponent = MyPawn->GetStaticMeshComponent();

			ActorRotation = StaticMeshComponent->GetComponentRotation();

			Pitch = ActorRotation.Pitch;

			Roll = ActorRotation.Roll;

			SpawnLocation = MyPawn->GetActorLocation();
		}
	}
}

void USpawnAnimComponent::PlayAnimation()
{
	SpawnAnimation.PlayFromStart();
}

