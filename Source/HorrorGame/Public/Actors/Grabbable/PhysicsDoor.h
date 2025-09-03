// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Grabbable.h"
#include "PhysicsDoor.generated.h"

UCLASS()
class HORRORGAME_API APhysicsDoor : public AActor, public IGrabbable
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Door;

	UPROPERTY(VisibleAnywhere)
	class UPhysicsConstraintComponent* PhysicsConstraint;

public:	
	// Sets default values for this actor's properties
	APhysicsDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
