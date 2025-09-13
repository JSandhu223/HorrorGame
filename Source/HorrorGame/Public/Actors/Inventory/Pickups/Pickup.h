// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class HORRORGAME_API APickup : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	class USphereComponent* CollisionSphere;

private:
	TSubclassOf<class AInventoryItem> Item;

	int32 Amount;
	
public:	
	// Sets default values for this actor's properties
	APickup();

private:
	void OnSphereOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
