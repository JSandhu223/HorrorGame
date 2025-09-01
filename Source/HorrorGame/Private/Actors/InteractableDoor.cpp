// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableDoor.h"
#include "Components/StaticMeshComponent.h"


AInteractableDoor::AInteractableDoor()
{
	UStaticMeshComponent* DoorFrame = GetComponentByClass<UStaticMeshComponent>();
	if (IsValid(DoorFrame))
	{
		DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
		DoorMesh->SetupAttachment(DoorFrame);
	}
}

void AInteractableDoor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacting with door!"));
}
