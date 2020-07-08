// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameModes/MyGameModeBase.h"
#include "Projectiles/Projectile.h"
#include "Engine/Engine.h"
#include "Pawns/MyPawn.h"
#include "PlayerControllers/MyPlayerController.h"
#include "GameFramework/DamageType.h"



// Sets default values
AEnemyBase::AEnemyBase()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AEnemyBase::OnEnemyHit);
	//StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnEnemyOverlap);

	EnemyHealthBar = CreateDefaultSubobject<UEnemyHealthBar>("EnemyHealthBar");
	EnemyHealthBar->SetupAttachment(StaticMeshComponent);

	SpawnAnimation = CreateDefaultSubobject<UEnemyAnimComponent>("SpawnAnimation");

	MovementComponent = CreateDefaultSubobject<UEnemyMovementComponent>("MovementComponent");

	FireComponent = CreateDefaultSubobject<UEnemyFireComponent>("FireComponent");

	OnTakeAnyDamage.AddDynamic(this, &AEnemyBase::ReceiveDamage);
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemyBase::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	if (Scale != FVector::OneVector)
	{
		SetUpScale(Scale);
	}

}

void AEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (MovementComponent != nullptr)
	{
		MovementComponent->MinSpeed = MinSpeed;
		MovementComponent->MaxSpeed = MaxSpeed;
		MovementComponent->DistanceFromPlayer = DistanceFromPlayer;
	}

	if (FireComponent != nullptr)
	{
		FireComponent->ProjectileClass = ProjectileClass;
		FireComponent->ProjectileColor = ProjectileColor;
	}

	
	

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	SetUpValues();

	SpawnAnimation->PlayAnimation();

	

	
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::SanitizeFloat(Health/MaxHealth));
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::SetUpValues()
{
	Health = MaxHealth;



	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (GameMode != nullptr)
	{
		GameMode->UpdateEnemyCount(0);
	}
}



void AEnemyBase::SetUpScale(FVector InScale)
{
	StaticMeshComponent->SetWorldScale3D(InScale);
}

void AEnemyBase::UpdateHealth()
{
	if (EnemyHealthBar != nullptr)
	{
		EnemyHealthBarWidget = Cast<UEnemyHealthBarWidget>(EnemyHealthBar->GetUserWidgetObject());
		if (EnemyHealthBarWidget != nullptr)
		{
			EnemyHealthBarWidget->UpdateHealth();
		}
	}
}

void AEnemyBase::OnEnemyHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor != nullptr)
	{
		AProjectile* Projectile = Cast<AProjectile>(OtherActor);

		if (!Projectile)
		{
			MovementComponent->bMoveDirection = !MovementComponent->bMoveDirection;
			
			if (OtherActor->IsA(AMyPawn::StaticClass()))
			{
				AMyPawn* MyPawn = Cast<AMyPawn>(OtherActor);

				if (MyPawn != nullptr)
				{
					UGameplayStatics::ApplyDamage(MyPawn, DamageValue, NULL, this, UDamageType::StaticClass());
				}
			}
			
		}
	}
	
}

/*void AEnemyBase::OnEnemyOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr)
	{
		AProjectile* Projectile = Cast<AProjectile>(OtherActor);

		if (!Projectile)
		{
			if (OtherActor->IsA(AMyPawn::StaticClass()))
			{
				AMyPawn* MyPawn = Cast<AMyPawn>(OtherActor);
				
				if (MyPawn != nullptr)
				{
					UGameplayStatics::ApplyDamage(MyPawn, DamageValue, NULL, this, UDamageType::StaticClass());
				}
			}
		}
	}
}*/

void AEnemyBase::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - Damage, 0.F, MaxHealth);

	UpdateHealth();

	if (Health <= 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);

		if (GameMode != nullptr)
		{
			GameMode->EnemyKilled();
		}

		Destroy();
	}
}


