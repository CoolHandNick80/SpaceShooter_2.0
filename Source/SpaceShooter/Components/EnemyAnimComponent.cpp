// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimComponent.h"
#include "GameModes/MyGameModeBase.h"
#include "Enemies/EnemyBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyAnimComponent::UEnemyAnimComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyAnimComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetupData();
}


// Called every frame
void UEnemyAnimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	SpawnAnimation.TickTimeline(DeltaTime);
}

void UEnemyAnimComponent::HandleProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(SpawnLocation, (SpawnLocation + SpawnForwardVector * (500.F)), Value);

	//GEngine->AddOnScreenDebugMessage(-1, 10.F, FColor::Cyan,(SpawnForwardVector.ToString()));

	MyEnemy->SetActorLocation(NewLocation);
}

void UEnemyAnimComponent::SetupData()
{
	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (EnemyCurve != nullptr)
	{
		//Bind Progress Function
		FOnTimelineFloat ProgressFunction;

		ProgressFunction.BindUFunction(this, "HandleProgress");

		SpawnAnimation.AddInterpFloat(EnemyCurve, ProgressFunction);

		//Bind EndFunction
		FOnTimelineEvent EndFunction;

		EndFunction.BindUFunction(this, "EnableMovement");

		SpawnAnimation.SetTimelineFinishedFunc(EndFunction);

		//Set variables
		MyEnemy = Cast<AEnemyBase>(GetOwner());
		verify(MyEnemy != nullptr);

		SpawnLocation = MyEnemy->GetActorLocation();

		SpawnForwardVector = MyEnemy->GetActorForwardVector();
	}
}

void UEnemyAnimComponent::PlayAnimation()
{
	//Start Timeline
	SpawnAnimation.PlayFromStart();
}

void UEnemyAnimComponent::EnableMovement()
{
	MyEnemy->bMoveEnabled = true;
}

           