// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Movement.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UMovement::UMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PlayerRef = nullptr;

	SprintSpeed = 800.0f;
	WalkSpeed = 400.0f;
	CurrentStamina = 0.0f;
	MaxStamina = 100.0f;
	MinStamina = 0.0f;
}

// Called when the game starts
void UMovement::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Movement component is active on %s"), *this->GetOwner()->GetName());
}


// Called every frame
void UMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMovement::Initialize(ACharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Initializing Movement component"));

	PlayerRef = Character;

	// Set the max walk speed on the character's existing character movement component to the walk speed of this custom movement component
	PlayerRef->GetCharacterMovement()->MaxWalkSpeed = this->WalkSpeed;
}