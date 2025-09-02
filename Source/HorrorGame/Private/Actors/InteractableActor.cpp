// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableActor.h"
#include "Game/Level1/L1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	this->RootComponent = SceneRoot;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerRef = Cast<AL1Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (!IsValid(PlayerRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("AInteractableActor: failed to cast PlayerRef to AL1Character"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("AInteractableActor PlayerRef: %s"), *PlayerRef->GetName());
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("InteractableActor hit!"));
}