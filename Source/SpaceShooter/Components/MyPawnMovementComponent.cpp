// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnMovementComponent.h"
#include "Pawns/MyPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UMyPawnMovementComponent::UMyPawnMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ATrack>MyTrackObject(TEXT("/Game/Blueprints/Track/BP_MyTrack"));
	
	MyTrackClass = MyTrackObject.Class;

	// ...
}


// Called when the game starts
void UMyPawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), MyTrackClass);

	if(Actor != nullptr)
	{
		Track = Cast<ATrack>(Actor);
	}
	

	SetupData();
}


// Called every frame
void UMyPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	PawnMover.TickTimeline(DeltaTime);

	MoveSpline(HozSpeed, ForwardSpeed, VertSpeed);
}

void UMyPawnMovementComponent::SetupData()
{
	MyPawn = Cast<AMyPawn>(GetOwner());
	verify(MyPawn != nullptr);
	if (MyPawn != nullptr)
	{
		BoxComponent = MyPawn->GetBoxComponent();

		StaticMeshComponent = MyPawn->GetStaticMeshComponent();
	}
	
	if (StaticMeshComponent != nullptr)
	{
		FRotator ActorRotation = StaticMeshComponent->GetComponentRotation();

		Roll = ActorRotation.Roll;
	}

	
	if (CurveFloat != nullptr)
	{
		PawnMover.SetPlayRate(1 / Duration);
		PawnMover.SetNewTime(PawnStartOffset);

		//bind progress function

		FOnTimelineFloat ProgressFunction;

		ProgressFunction.BindUFunction(this, "HandleProgress");

		PawnMover.AddInterpFloat(CurveFloat, ProgressFunction);

		//bind end function

		FOnTimelineEvent EndFunction;

		EndFunction.BindUFunction(this, "EndTrack");

		PawnMover.SetTimelineFinishedFunc(EndFunction);
	}

	if (Track != nullptr)
	{
		USplineComponent* SplineComponent = Track->GetSplineComponent();
		if (SplineComponent != nullptr)
		{
			LastSplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(0.F, ESplineCoordinateSpace::World);
			LastSplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(0.F, ESplineCoordinateSpace::World);
		}
		
	}
}

void UMyPawnMovementComponent::SetHorizontalInput(float amount)
{
	LastInput.Y += amount;
}

void UMyPawnMovementComponent::SetForwardInput(float amount)
{
	LastInput.X += amount;
}

void UMyPawnMovementComponent::SetVerticalInput(float amount)
{
	LastInput.Z += amount;
}

void UMyPawnMovementComponent::SetHorizontalSpeed(float Val)
{
	HozSpeed = SetSpeed(HozSpeed, Val);
}

void UMyPawnMovementComponent::SetForwardSpeed(float Val)
{
	ForwardSpeed = SetSpeed(ForwardSpeed, Val);
}

void UMyPawnMovementComponent::SetVerticalSpeed(float Val)
{
	VertSpeed = SetSpeed(VertSpeed, Val);
}

void UMyPawnMovementComponent::Move(float InHozSpeed, float InForwardSpeed, float InVerticalSpeed)
{
	float Lenght = LastInput.Size();

	if (Lenght > 1.F)
	{
		LastInput /= Lenght;
	}

	SetForwardSpeed(LastInput.X);
	SetHorizontalSpeed(LastInput.Y);
	SetVerticalSpeed(LastInput.Z);

	FVector RootLocation = MyPawn->GetActorLocation();

	FVector ForwardLocation = BoxComponent->GetRelativeLocation() + FVector::ForwardVector*ForwardSpeed;
	FVector HorizontalLocation = BoxComponent->GetRelativeLocation() + FVector::RightVector*HozSpeed;
	FVector VerticalLocation = BoxComponent->GetRelativeLocation() + FVector::UpVector*VertSpeed;

	if (FMath::Abs(ForwardLocation.X) <= MaxForwardDistance)
	{ 
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::SanitizeFloat(FMath::Abs(ForwardLocation.X)));
		
		BoxComponent->SetRelativeLocation(BoxComponent->GetRelativeLocation() + FVector::ForwardVector*ForwardSpeed, true);
	}
	

	if (FMath::Abs(HorizontalLocation.Y) <= MaxHorizontalDistance)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::SanitizeFloat(FMath::Abs(HorizontalLocation.Y)));

		BoxComponent->SetRelativeLocation(BoxComponent->GetRelativeLocation() + FVector::RightVector*HozSpeed, true);
	}
	
	
	if (FMath::Abs(VerticalLocation.Z) <= MaxVerticalDistance)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::SanitizeFloat(FMath::Abs(VerticalLocation.Z)));

		BoxComponent->SetRelativeLocation(BoxComponent->GetRelativeLocation() + FVector::UpVector*VertSpeed, true);
	}
	
	StaticMeshComponent->SetRelativeRotation(FMath::RInterpConstantTo(StaticMeshComponent->GetRelativeRotation(), FRotator(StaticMeshComponent->GetRelativeRotation().Pitch, StaticMeshComponent->GetRelativeRotation().Yaw, (Roll + HozSpeed * 7)), GetWorld()->GetDeltaSeconds(), 80.F));

	LastInput = FVector::ZeroVector;
}

void UMyPawnMovementComponent::MoveSpline(float InHozSpeed, float InForwardSpeed, float InVerticalSpeed)
{
	float Lenght = LastInput.Size();

	if (Lenght > 1.F)
	{
		LastInput /= Lenght;
	}

	SetForwardSpeed(LastInput.X);
	SetHorizontalSpeed(LastInput.Y);
	SetVerticalSpeed(LastInput.Z);

	if (MyPawn != nullptr)
	{
		FVector ForwardLocation = MyPawn->GetActorLocation() + FVector::ForwardVector*ForwardSpeed;
		FVector HorizontalLocation = MyPawn->GetActorLocation() + FVector::RightVector*HozSpeed;
		FVector VerticalLocation = MyPawn->GetActorLocation() + FVector::UpVector*VertSpeed;

		//GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Red, DiffVector.ToString());

		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::SanitizeFloat(FMath::Abs(ForwardLocation.X)));

		MyPawn->SetActorLocation(MyPawn->GetActorLocation() + FVector(DiffVector.X, 0.F, 0.F) + (FVector::ForwardVector*ForwardSpeed), true);



		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::SanitizeFloat(FMath::Abs(HorizontalLocation.Y)));

		MyPawn->SetActorLocation(MyPawn->GetActorLocation() + FVector(0.F, DiffVector.Y, 0.F) + (FVector::RightVector*HozSpeed), true);



		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::SanitizeFloat(FMath::Abs(VerticalLocation.Z)));

		MyPawn->SetActorLocation(MyPawn->GetActorLocation() + FVector(0.F, 0.F, DiffVector.Z) + (FVector::UpVector*VertSpeed), true);

		MyPawn->SetActorRotation(MyPawn->GetActorRotation() + DiffRotator);

		if (StaticMeshComponent != nullptr)
		{
			StaticMeshComponent->SetRelativeRotation(FMath::RInterpConstantTo(StaticMeshComponent->GetRelativeRotation(), FRotator(StaticMeshComponent->GetRelativeRotation().Pitch, StaticMeshComponent->GetRelativeRotation().Yaw, (Roll + HozSpeed * 7)), GetWorld()->GetDeltaSeconds(), 80.F));
		}
	}

	LastInput = FVector::ZeroVector;

}

float UMyPawnMovementComponent::SetSpeed(float Speed, float Value)
{
	Speed = FMath::FInterpTo(Speed, (MovementSpeed*Value), GetWorld()->GetDeltaSeconds(), 6);

	return Speed;
}

void UMyPawnMovementComponent::StartTrack()
{
	PawnMover.PlayFromStart();
}

void UMyPawnMovementComponent::HandleProgress(float Value)
{
	if (Track != nullptr)
	{
		USplineComponent* SplineComponent = Track->GetSplineComponent();
		if (SplineComponent != nullptr)
		{
			float Distance = FMath::Lerp(0.F, (SplineComponent->GetSplineLength()), Value);
			
			NewSplineLocation = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
			NewSplineRotation = SplineComponent->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

			DiffVector = NewSplineLocation - LastSplineLocation;
			DiffRotator = NewSplineRotation - LastSplineRotation;

			LastSplineLocation = NewSplineLocation;
			LastSplineRotation = NewSplineRotation;

			//GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Magenta, DiffVector.ToString());
		}
		

		/*FHitResult HitResult;
		const FVector& Start = BoxComponent->GetComponentLocation();
		const FVector& End = Start + BoxComponent->GetForwardVector()*1000.F;
		FCollisionQueryParams CollisionParams;

		CollisionParams.AddIgnoredActor(MyPawn);


		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, -1.F, (uint8)'\000', 1.F);*/

		//MyPawn->SetActorLocation(NewLocation, true);
		
		
		
		/*if (HitResult.bBlockingHit)
		{
		GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Green, HitResult.ToString());
		}*/
		

		//MyPawn->SetActorRotation(NewRotation);
	}
}

void UMyPawnMovementComponent::EndTrack()
{
	DiffVector = FVector::ZeroVector;

	DiffRotator = FRotator::ZeroRotator;
}

