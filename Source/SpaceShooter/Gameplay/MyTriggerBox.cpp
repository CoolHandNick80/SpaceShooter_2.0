// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ShapeComponent.h"
#include "Engine/Engine.h"


void AMyTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(GameMode != nullptr);

	StartTimer();
}

void AMyTriggerBox::SpawnFunction(UClass * InClass)
{
	if (InClass != nullptr)
	{
		const FVector& SpawnLocation = GetRandomLocation();

		const FRotator& SpawnRotation = GetActorRotation();

		FTransform SpawnTransform = FTransform(FRotator::FRotator(0.F, (SpawnRotation.Yaw + 180.F), 0.F), SpawnLocation, FVector::OneVector);

		AEnemyBase* NewEnemy = Cast<AEnemyBase>( GetWorld()->SpawnActor<AActor>(InClass, SpawnTransform));

		if (NewEnemy != nullptr)
		{
			NewEnemy->MyTriggerBox = this;
		}
	}
}

void AMyTriggerBox::SpawnFunction(UClass * InClass, float InDelay)
{
	FTimerHandle TimerHandle;

	FTimerDelegate Delegate;

	Delegate.BindUFunction(this, "SpawnFunction", InClass);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, InDelay, false);
}

void AMyTriggerBox::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnEnemiesTimerHandle, this, &AMyTriggerBox::UpdateTimer, 1.F, true);
}

void AMyTriggerBox::UpdateTimer()
{
	if(GameMode != nullptr)
	{
		if (GameMode->GetEnemyCount() < GameMode->GetMaxEnemies())
		{
			if (GameMode->GetEnemiesKilled() % 5 == 0 && GameMode->GetEnemiesKilled() != CurrentEnemiesKilled)
			{
				CurrentEnemiesKilled = GameMode->GetEnemiesKilled();

				SpawnFunction(EnemyTwoClass);

				GameMode->UpdateEnemyCount(1);
			}
			else
			{
				float Delay = FMath::RandRange(0.5F, 2.F);

				SpawnFunction(EnemyOneClass, Delay);

				GameMode->UpdateEnemyCount(1);
			}
		}
		else
		{
			//StopTimer();
		}


		int32 MaxAsteroidsNumber = FMath::RandRange(1, 3);

		for (int32 i = 0; i <= MaxAsteroidsNumber; i++)
		{
			float Delay = FMath::RandRange(0.5F, 3.F);

			SpawnFunction(AsteroidClass, Delay);
		}
	}
	
}

void AMyTriggerBox::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnEnemiesTimerHandle);
}




FVector AMyTriggerBox::GetRandomLocation()
{
	//FVector Origin; 
	//FVector BoxExtent; 
	float SphereRadius = 0.F;
	
	const FVector BoxLocation = GetActorLocation();

	const FTransform BoxTransform = GetActorTransform();

	const UShapeComponent* CollisionComp = GetCollisionComponent();

	

	if (CollisionComp != nullptr)
	{
		FBoxSphereBounds Bounds = CollisionComp->CalcBounds(GetActorTransform());

		FVector BoxExtent = FVector(0.F, Bounds.BoxExtent.Y, Bounds.BoxExtent.Z);

		FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, BoxExtent);

		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Emerald, RandomPoint.ToString());
		
		FVector NewPoint = BoxTransform.TransformPosition(RandomPoint);

		return NewPoint;

	}
	return BoxLocation;
}
