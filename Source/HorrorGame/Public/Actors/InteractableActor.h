// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "InteractableActor.generated.h"

UCLASS()
class HORRORGAME_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	class AL1Character* PlayerRef;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

	virtual void Interact() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
