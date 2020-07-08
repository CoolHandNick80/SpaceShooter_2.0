// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/MyGameModeBase.h"
#include "Engine/Engine.h"
#include "GameInstances/MyGameInstance.h"
#include "Enemies/EnemyBase.h"
#include "GameFramework/DamageType.h"
#include "PlayerControllers/MyPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Gameplay/Track.h"





// Sets default values
AMyPawn::AMyPawn()
{
	//SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	//RootComponent = SceneComponent;


	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	//BoxComponent->SetupAttachment(SceneComponent);
	RootComponent = BoxComponent;
	BoxComponent->SetBoxExtent(FVector(18.F, 22.5F, 7.5F));

	BoxComponent->OnComponentHit.AddDynamic(this, &AMyPawn::OnEnemyHit);
	//BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::OnEnemyOverlap);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(BoxComponent);
	
	StaticMeshComponent->SetWorldLocation(FVector(-5.F, 0.F, 0.F));

	PrimaryFireSpawn = CreateDefaultSubobject<UFireComponent>("PrimaryFire");
	PrimaryFireSpawn->SetupAttachment(StaticMeshComponent);
	PrimaryFireSpawn->SetRelativeLocation(FVector(20.F, 0.F, 0.F));

	SecondaryFireLeft = CreateDefaultSubobject<UFireComponent>("SecondaryFireLeft");
	SecondaryFireLeft->SetupAttachment(StaticMeshComponent);
	SecondaryFireLeft->SetRelativeLocation(FVector(15.F, -5.F, 0.F));

	SecondaryFireRight = CreateDefaultSubobject<UFireComponent>("SecondaryFireRight");
	SecondaryFireRight->SetupAttachment(StaticMeshComponent);
	SecondaryFireRight->SetRelativeLocation(FVector(15.F, 5.F, 0.F));

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	ParticleSystem->SetupAttachment(StaticMeshComponent);

	CrossHairComponent = CreateDefaultSubobject<UCrossHairComponent>("CrossHairComponent");
	CrossHairComponent->SetupAttachment(StaticMeshComponent);

	MyPawnMovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>("MyPawnMovementComponent");

	SpawnAnimComponent = CreateDefaultSubobject<USpawnAnimComponent>("SpawnAnimComponent");

	OnTakeAnyDamage.AddDynamic(this, &AMyPawn::ReceiveDamage);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	SpawnAnimComponent->PlayAnimation();
	//bMoveEnabled = true;

	//MyPawnMovementComponent->StartTrack();
	
	GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	verify(GameMode != nullptr);

	GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	verify(GameInstance != nullptr);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	const FVector& Start = PrimaryFireSpawn->GetComponentLocation();
	const FVector& End = Start + PrimaryFireSpawn->GetForwardVector()*1000.F;
	FCollisionQueryParams CollisionParams;
	
	CollisionParams.AddIgnoredActor(this);
	

	GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,ECC_Visibility,CollisionParams);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.F, (uint8)'\000', 1.F);
	
	if (HitResult.bBlockingHit)
	{
		if (!Cast<AProjectile>(HitResult.Actor) && !Cast<ATrack>(HitResult.Actor))
		{
			CrossHairComponent->SetWorldLocation(HitResult.Location);
			CrossHairComponent->GetUserWidgetObject()->SetColorAndOpacity(FColor::Red);
			GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Blue, HitResult.Actor->GetName());

		}
		else
		{
			CrossHairComponent->SetRelativeLocation(FVector::ForwardVector * 500);
			CrossHairComponent->GetUserWidgetObject()->SetColorAndOpacity(FColor::White);
		}
	}
	else
	{
		CrossHairComponent->SetRelativeLocation(FVector::ForwardVector * 500);
		CrossHairComponent->GetUserWidgetObject()->SetColorAndOpacity(FColor::White);
	}
}

// Called after the Actor's components have been initialized
void AMyPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Set Primary Fire Projectile class, color and rate
	PrimaryFireSpawn->ProjectileClass = PrimaryProjectileClass;
	PrimaryFireSpawn->ProjectileColor = PrimaryProjectileColor;
	PrimaryFireSpawn->RateOfFire = PrimaryProyectileRate;

	// Set Secondary Fire Projectile class and color
	SecondaryFireLeft->ProjectileClass = SecondaryProjectileClass;
	SecondaryFireLeft->ProjectileColor = SecondaryProjectileColor;
	SecondaryFireLeft->RateOfFire = SecondaryProjectileRate;

	SecondaryFireRight->ProjectileClass = SecondaryProjectileClass;
	SecondaryFireRight->ProjectileColor = SecondaryProjectileColor;
	SecondaryFireRight->RateOfFire = SecondaryProjectileRate;


}

void AMyPawn::ReceiveDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	GameInstance->UpdateHealth(Damage);

	if (GameInstance->GetPlayerData().Health <= 0)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), NULL, GetActorLocation());

		if (GameMode != nullptr)
		{
			GameMode->PlayCamShake(NULL, GetActorLocation());
			GameMode->GameOver();
		}

		Destroy();
	}

}

/*void AMyPawn::OnEnemyOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr)
	{
		AProjectile* Projectile = Cast<AProjectile>(OtherActor);

		if (!Projectile)
		{
			if (OtherActor->IsA(AEnemyBase::StaticClass()))
			{
				AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
				if (Enemy != nullptr)
				{
					AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
					if (MyPlayerController != nullptr)
					{
						UGameplayStatics::ApplyDamage(Enemy, DamageValue, MyPlayerController, this, UDamageType::StaticClass());
					}
				}
			}
		}
	}
}*/

void AMyPawn::OnEnemyHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor != nullptr)
	{
		AProjectile* Projectile = Cast<AProjectile>(OtherActor);

		if (!Projectile)
		{
			if (OtherActor->IsA(AEnemyBase::StaticClass()))
			{
				AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
				if (Enemy != nullptr)
				{
					AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
					if (MyPlayerController != nullptr)
					{
						UGameplayStatics::ApplyDamage(Enemy, DamageValue, MyPlayerController, this, UDamageType::StaticClass());
					}
				}
			}
		}
	}
}










