// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawnMovementComponent.h"
#include "Pawns/MyPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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

/*Deprecated function*/
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

	if (MyPawn != nullptr)
	{
		MyPawn->SetActorLocation(MyPawn->GetActorLocation() + FVector::ForwardVector*ForwardSpeed, true);
		MyPawn->SetActorLocation(MyPawn->GetActorLocation() + FVector::RightVector*HozSpeed, true);
		MyPawn->SetActorLocation(MyPawn->GetActorLocation() + FVector::UpVector*VertSpeed, true);
		
		StaticMeshComponent->SetRelativeRotation(FMath::RInterpConstantTo(StaticMeshComponent->GetRelativeRotation(), FRotator(StaticMeshComponent->GetRelativeRotation().Pitch, StaticMeshComponent->GetRelativeRotation().Yaw, (Roll + HozSpeed * 7)), GetWorld()->GetDeltaSeconds(), 80.F));

		LastInput = FVector::ZeroVector;
	}
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
		ForwardLocation += FVector::ForwardVector * ForwardSpeed;
		HorizontalLocation += FVector::RightVector * HozSpeed;
		VerticalLocation += FVector::UpVector * VertSpeed;

		if (FMath::Abs(ForwardLocation.X) >= MaxForwardDistance)
		{
			if (ForwardLocation.X > 0)
			{
				ForwardLocation.X = MaxForwardDistance;
			}
			else
			{
				ForwardLocation.X = -MaxForwardDistance;
			}
		}
		
		if (FMath::Abs(HorizontalLocation.Y) >= MaxHorizontalDistance)
		{
			if (HorizontalLocation.Y > 0)
			{
				HorizontalLocation.Y = MaxHorizontalDistance;
			}
			else
			{
				HorizontalLocation.Y = -MaxHorizontalDistance;
			}
		}
		
		if (FMath::Abs(VerticalLocation.Z) >= MaxVerticalDistance)
		{
			if (VerticalLocation.Z > 0)
			{
				VerticalLocation.Z = MaxVerticalDistance;
			}
			else
			{
				VerticalLocation.Z = -MaxVerticalDistance;
			}
			
		}
		
		FVector New = FVector(ForwardLocation.X, HorizontalLocation.Y, VerticalLocation.Z);
		
		FVector NewLocation = UKismetMathLibrary::TransformLocation(NewSplineTransform, New);
		
		FVector RelativeLocation = UKismetMathLibrary::InverseTransformLocation(NewSplineTransform, NewLocation);

		GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Purple, RelativeLocation.ToString());
		
		MyPawn->SetActorLocation(NewLocation, true);

		MyPawn->SetActorRotation(NewSplineRotation);

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
			NewSplineTransform = SplineComponent->GetTransformAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);	
		}
	}
}

void UMyPawnMovementComponent::EndTrack()
{
	
}

