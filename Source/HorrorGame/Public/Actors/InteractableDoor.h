// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractableActor.h"
#include "Components/TimelineComponent.h"
#include "InteractableDoor.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API AInteractableDoor : public AInteractableActor
{
	GENERATED_BODY()

private:
	bool bIsDoorClosed;

	float DotProduct;

	float TargetYaw;

	// This will be attached to the inherited mesh, which we'll set to be the doorframe
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* DoorTimeline;

	// Variable to hold the Curve asset
	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat* DoorTimelineFloatCurve;

	// Float Track Signature to handle our update track event
	FOnTimelineFloat UpdateFunctionFloat;

	// Function which updates our Door's relative location with the timeline graph
	UFUNCTION()
	void UpdateTimelineComp(float Output);

protected:
	virtual void BeginPlay() override;

public:
	AInteractableDoor();
	
	virtual void Interact() override;
};
