// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Actors/InteractableActor.h"
#include "Game/Level1/L1Character.h"
#include "Kismet/KismetMathLibrary.h"


AInteractableDoor::AInteractableDoor()
{
	bIsDoorClosed = true;

	DotProduct = 0.0f;

	TargetYaw = 0.0f;

	UStaticMeshComponent* DoorFrame = GetComponentByClass<UStaticMeshComponent>();
	if (IsValid(DoorFrame))
	{
		DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
		DoorMesh->SetupAttachment(DoorFrame);

		DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
	}
}

void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloat.BindDynamic(this, &AInteractableDoor::UpdateTimelineComp);

	// If we have a float curve, bind it's graph to our update function
	if (DoorTimelineFloatCurve)
	{
		DoorTimeline->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
}

void AInteractableDoor::UpdateTimelineComp(float Output)
{
	float CurrentDoorYaw = static_cast<float>(DoorMesh->GetComponentRotation().Yaw);
	if (DotProduct >= 0.0f)
	{
		//if (CurrentDoorYaw >= 0.0f)
		if (FMath::IsNegative(CurrentDoorYaw))
			TargetYaw = -Output;
		else
			TargetYaw = Output;
	}
	else
	{
		if (!FMath::IsNegative(CurrentDoorYaw) && CurrentDoorYaw != 0.0f)
			TargetYaw = Output;
		else
			TargetYaw = -Output;
	}

	if (FMath::IsNearlyZero(TargetYaw, 1.0E-5))
	{
		//UE_LOG(LogTemp, Warning, TEXT("TargetYaw is nearly zero"));
		TargetYaw = 0.0f;
	}
	FRotator DoorNewRotation = FRotator(0.0f, TargetYaw, 0.0f);
	DoorMesh->SetRelativeRotation(DoorNewRotation);

	//UE_LOG(LogTemp, Warning, TEXT("TargetYaw: %f"), TargetYaw);
	//UE_LOG(LogTemp, Warning, TEXT("CurrentDoorYaw: %lf"), CurrentDoorYaw);
}

void AInteractableDoor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting with door!"));

	FVector Distance = this->GetActorLocation() - PlayerRef->GetActorLocation();
	DotProduct = FVector::DotProduct(this->GetActorForwardVector(), UKismetMathLibrary::Normal(Distance));
	//UE_LOG(LogTemp, Warning, TEXT("DotProduct: %f"), DotProduct);
	
	if (bIsDoorClosed)
	{
		DoorTimeline->Play();
		bIsDoorClosed = false;
	}
	else
	{
		DoorTimeline->Reverse();
		bIsDoorClosed = true;
	}
}
