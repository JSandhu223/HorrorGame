// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Grabbable/PhysicsDoor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
APhysicsDoor::APhysicsDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	this->RootComponent = SceneRoot;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(SceneRoot);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);
}

// Called when the game starts or when spawned
void APhysicsDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicsDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

