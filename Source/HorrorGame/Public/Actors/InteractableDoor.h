// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "InteractableDoor.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API AInteractableDoor : public AInteractableActor
{
	GENERATED_BODY()

private:
	// This will be attached to the inherited mesh, which we'll set to be the doorframe
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DoorMesh;

public:
	AInteractableDoor();
	
};
