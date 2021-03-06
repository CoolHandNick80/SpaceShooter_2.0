// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameplayCamera.h"
#include "Pawns/MyPawn.h"


// Sets default values
AMyGameplayCamera::AMyGameplayCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(SceneComponent);
	SpringArmComponent->SetWorldRotation(FRotator(0.F, 0.F, 0.F));
	SpringArmComponent->TargetArmLength = 200;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocation(FVector(0.F, 0.F, 0.F));
}

// Called when the game starts or when spawned
void AMyGameplayCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyGameplayCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateGameplayCamera();

}

void AMyGameplayCamera::UpdateGameplayCamera()
{
	if (TargetActor != nullptr)
	{
		AMyPawn* MyPawn = Cast<AMyPawn>(TargetActor);
		if (MyPawn != nullptr)
		{
			if (MyPawn->bMoveEnabled == true)
			{
				SetActorLocation(MyPawn->GetActorLocation());
				SetActorRotation(MyPawn->GetActorRotation());
			}
		}
	}
}

