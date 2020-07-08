// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Pawns/MyPawn.h"
#include "PlayerControllers/MyPlayerController.h"
#include "GameFramework/DamageType.h"

// Sets default values
AAsteroid::AAsteroid()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AAsteroid::OnEnemyHit);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(StaticMeshComponent);


	OnTakeAnyDamage.AddDynamic(this, &AAsteroid::ReceiveDamage);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AAsteroid::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	if (Scale != FVector::OneVector)
	{
		SetUpScale(Scale);
	}
	
	Speed = FMath::RandRange(MinSpeed, MaxSpeed);

	if (ProjectileMovementComponent != nullptr)
	{
		ProjectileMovementComponent->MaxSpeed = Speed;
		ProjectileMovementComponent->InitialSpeed = Speed;
		ProjectileMovementComponent->Velocity = FVector::ForwardVector;
		ProjectileMovementComponent->ProjectileGravityScale = 0.F;
	}
}

void AAsteroid::PostInitializeComponents()
{
	Super::PostInitializeComponents();	
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	StartTimer();
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 1.F, FColor::Emerald, FString::SanitizeFloat(Speed));
}

void AAsteroid::SetUpScale(FVector InScale)
{
	StaticMeshComponent->SetWorldScale3D(InScale);
}

void AAsteroid::OnEnemyHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor != nullptr)
	{
		if (OtherActor->IsA(AMyPawn::StaticClass()))
		{

			AMyPawn* MyPawn = Cast<AMyPawn>(OtherActor);
			if (MyPawn != nullptr)
			{
				AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
				if (MyPlayerController != nullptr)
				{
					UGameplayStatics::ApplyDamage(MyPawn, DamageValue, MyPlayerController, this, UDamageType::StaticClass());
				}
			}
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, Hit.Location, FRotator::ZeroRotator, true);

	Destroy();
}

void AAsteroid::ReceiveDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	Health = FMath::Clamp(Health - Damage, 0.F, MaxHealth);

	if (Health <= 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);

		GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));

		if (GameInstance != nullptr)
		{
			GameInstance->UpdateScore(EnemyScoreValue);
		}

		Destroy();
	}
}

void AAsteroid::StartTimer()
{
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAsteroid::Explode, LifeTime);
}

void AAsteroid::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);

	Destroy();
}

