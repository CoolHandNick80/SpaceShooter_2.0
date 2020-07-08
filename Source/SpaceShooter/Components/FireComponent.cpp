// Fill out your copyright notice in the Description page of Project Settings.

#include "FireComponent.h"
#include "Pawns/MyPawn.h"
#include "TimerManager.h "
#include "Projectiles/Projectile.h"

// Sets default values for this component's properties
UFireComponent::UFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UFireComponent::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = Cast<AMyPawn>(GetOwner());
	verify(MyPawn != nullptr);
	
}


// Called every frame
void UFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFireComponent::Fire()
{
	if (ProjectileClass != nullptr)
	{
		FTransform SpawnTransform = GetComponentTransform();

		AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform, MyPawn, MyPawn, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->ProjectileColor = ProjectileColor;

		Projectile->FinishSpawning(SpawnTransform);
	}
}

void UFireComponent::StartTimer()
{
	if (MyPawn->bMoveEnabled == true)
	{
		if (bIsFiring == false)
		{
			bFirePressed = true;

			GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UFireComponent::UpdateTimer, RateOfFire, true, 0.F);
		}
		else
		{
			bFirePressed = true;
		}
	}
}

void UFireComponent::UpdateTimer()
{
	if (bFirePressed == false)
	{
		if (bIsFiring == false)
		{
			GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
		}
		else
		{
			bIsFiring = false;
		}
	}
	else
	{
		if (bIsFiring == false)
		{
			Fire();
			bIsFiring = true;
		}
		else
		{
			Fire();
		}
	}
}

void UFireComponent::StopTimer()
{
	bFirePressed = false;
}

