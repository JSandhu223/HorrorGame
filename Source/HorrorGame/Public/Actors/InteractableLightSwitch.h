// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "InteractableLightSwitch.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API AInteractableLightSwitch : public AInteractableActor
{
	GENERATED_BODY()
	
private:
	// This will be set on each instance of this actor placed in our level
	UPROPERTY(EditAnywhere)
	class ALight* Light;

public:
	virtual void Interact() override;
};
