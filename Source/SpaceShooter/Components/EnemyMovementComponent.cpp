// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"
#include "GameModes/MyGameModeBase.h"
#include "Enemies/EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ShapeComponent.h"
#include "Gameplay/MyTriggerBox.h"



// Sets default values for this component's properties
UEnemyMovementComponent::UEnemyMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetupData();
}


// Called every frame
void UEnemyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	EnemyMovement(DeltaTime);
}

//Set variables
void UEnemyMovementComponent::SetupData()
{
	bMoveDirection = UKismetMathLibrary::RandomBool();

	MovementSpeed = FMath::FRandRange(MinSpeed, MaxSpeed);

	MyEnemy = Cast<AEnemyBase>(GetOwner());
	verify(MyEnemy != nullptr);
}

void UEnemyMovementComponent::EnemyMovement(float DeltaSeconds)
{
	if (MyEnemy != nullptr)
	{
		if (MyEnemy->MyTriggerBox != nullptr)
		{
			if (MyEnemy->bMoveEnabled == true)
			{
				FVector NewLocation = MyEnemy->GetActorLocation() + MyEnemy->GetActorRightVector()*(MovementSpeed * UKismetMathLibrary::SelectFloat(1, -1, bMoveDirection))*DeltaSeconds;

				const FVector BoxLocation = MyEnemy->MyTriggerBox->GetActorLocation();
				const UShapeComponent* CollisionComp = MyEnemy->MyTriggerBox->GetCollisionComponent();
				if (CollisionComp != nullptr)
				{
					FBoxSphereBounds Bounds = CollisionComp->CalcBounds(MyEnemy->MyTriggerBox->GetActorTransform());


					FVector2D NewLocation2D = FVector2D(NewLocation.X, NewLocation.Y);
					FVector2D OriginLocation2D = FVector2D(Bounds.Origin.X, Bounds.Origin.Y);
					FVector2D Pivot = FVector2D(MyEnemy->MyTriggerBox->GetActorForwardVector().X, MyEnemy->MyTriggerBox->GetActorForwardVector().Y) * -500.F;
					FVector2D DiffVec = NewLocation2D - (OriginLocation2D + Pivot);

					//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, Pivot.ToString());
					//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Black, FString::SanitizeFloat(DiffVec.Size()));
					//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Silver, FString::SanitizeFloat(Bounds.BoxExtent.Y));



					if (DiffVec.Size() <= Bounds.BoxExtent.Y)
					{

						MyEnemy->SetActorLocation(NewLocation, true);
					}
					else
					{
						bMoveDirection = !bMoveDirection;
					}
				}
			}
		}
	}
}