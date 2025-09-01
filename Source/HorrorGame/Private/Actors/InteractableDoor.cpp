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
	FRotator DoorNewRotation = FRotator(0.0f, Output, 0.0f);
	DoorMesh->SetRelativeRotation(DoorNewRotation);

	UE_LOG(LogTemp, Warning, TEXT("Output: %f"), Output);
}

void AInteractableDoor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting with door!"));

	FVector Distance = this->GetActorLocation() - PlayerRef->GetActorLocation();
	DotProduct = FVector::DotProduct(this->GetActorForwardVector(), UKismetMathLibrary::Normal(Distance));
	UE_LOG(LogTemp, Warning, TEXT("DotProduct: %f"), DotProduct);
	
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
