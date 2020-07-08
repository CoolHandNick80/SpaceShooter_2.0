// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireComponent.h"
#include "Pawns/MyPawn.h"
#include "Enemies/EnemyBase.h"
#include "Projectiles/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UEnemyFireComponent::UEnemyFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFireComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetupData();
}


// Called every frame
void UEnemyFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	CheckDistance();
}

void UEnemyFireComponent::SetupData()
{
	MyPawn = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	//verify(MyPawn != nullptr);

	MyOwner = Cast<AEnemyBase>(GetOwner());
	verify(MyOwner != nullptr);
}

float UEnemyFireComponent::GetDistanceFromPlayer()
{
	if (MyPawn != nullptr && MyOwner != nullptr) 
	{
		FVector Vector = (MyPawn->GetActorLocation() - MyOwner->GetActorLocation()) * FVector(1.F, 0.F, 0.F);

		return Vector.Size();
	}

	return 0.F;
}

void UEnemyFireComponent::CheckDistance()
{
	if (MyPawn != nullptr && MyOwner != nullptr)
	{
		if (GetDistanceFromPlayer() <= MyOwner->GetMaxDistanceFromPlayer())
		{
			if (bIsInRange == false)
			{
				StartTimer();
				bIsInRange = true;
			}				
		}
		else
		{
			if (bIsInRange == true)
			{
				StopTimer();
				bIsInRange = false;
			}
		}
	}
}

void UEnemyFireComponent::Fire()
{
	if (ProjectileClass != nullptr)
	{
		FTransform SpawnTransform = MyOwner->GetActorTransform();

		AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform, MyOwner, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->ProjectileColor = ProjectileColor;

		Projectile->FinishSpawning(SpawnTransform);
	}
}


void UEnemyFireComponent::StartTimer()
{
	float Delay = FMath::RandRange(0.1F, 0.4F);

	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UEnemyFireComponent::Fire, RateOfFire, true, Delay);
}


void UEnemyFireComponent::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}


