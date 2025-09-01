// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"


AInteractableDoor::AInteractableDoor()
{
	bIsDoorClosed = true;

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

	//If we have a float curve, bind it's graph to our update function
	if (DoorTimelineFloatCurve)
	{
		DoorTimeline->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
}

void AInteractableDoor::UpdateTimelineComp(float Output)
{
	// Create and set our Door's new relative location based on the output from our Timeline Curve
	FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
	DoorMesh->SetRelativeRotation(DoorNewRotation);
}

void AInteractableDoor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting with door!"));
	
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
