// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Movement.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/TimerHandle.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Game/Level1/L1Character.h"


// Sets default values for this component's properties
UMovement::UMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PlayerRef = nullptr;

	SprintSpeed = 800.0f;
	WalkSpeed = 400.0f;
	MaxStamina = 100.0f;
	MinStamina = 0.0f;
	CurrentStamina = 100.0f;

	// These will be used with their respective timers
	StaminaDepletionRate = 0.1f;
	StaminaRegenRate = 0.05f;

	CrouchSpeed = 100.0f;
	CrouchHalfHeight = 44.0f;
	bIsCrouched = false;
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

void UMovement::SetPlayerMaxWalkSpeed(float MaxWalkSpeed)
{
	PlayerRef->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void UMovement::StartSprint()
{
	// If the player sprints while crouching
	if (bIsCrouched)
	{
		StopCrouch();
	}

	bool bPlayerHasStamina = CurrentStamina > MinStamina;
	bool bPlayerIsMoving = PlayerRef->GetVelocity().Length() > 0.0f;

	if (bPlayerHasStamina && bPlayerIsMoving)
	{
		SetPlayerMaxWalkSpeed(SprintSpeed);

		this->GetOwner()->GetWorldTimerManager().SetTimer(
			this->DepleteStaminaTimerHandle,
			this,
			&UMovement::DepleteStamina,
			StaminaDepletionRate,
			true
		);
	}
}

void UMovement::StopSprint()
{
	if (bIsCrouched) { return; }

	this->GetOwner()->GetWorldTimerManager().ClearTimer(this->DepleteStaminaTimerHandle);

	SetPlayerMaxWalkSpeed(this->WalkSpeed);

	float DelaySeconds = 5.0f;
	this->GetOwner()->GetWorldTimerManager().SetTimer(
		this->RegenerateStaminaTimerHandle,
		this,
		&UMovement::RegenerateStamina,
		StaminaRegenRate,
		true,
		DelaySeconds
	);
}

void UMovement::DepleteStamina()
{
	bool bPlayerIsMoving = PlayerRef->GetVelocity().Length() > 0.0f;
	if (!bPlayerIsMoving)
	{
		StopSprint();
		return;
	}

	CurrentStamina = FMath::Clamp(CurrentStamina - 1, MinStamina, MaxStamina);
	UE_LOG(LogTemp, Warning, TEXT("Depleted stamina! CurrentStamina: %f"), this->CurrentStamina);

	if (CurrentStamina == MinStamina)
	{
		StopSprint();
	}
}

void UMovement::RegenerateStamina()
{
	if (this->GetOwner()->GetWorldTimerManager().IsTimerActive(DepleteStaminaTimerHandle))
	{
		this->GetOwner()->GetWorldTimerManager().ClearTimer(this->RegenerateStaminaTimerHandle);
	}

	CurrentStamina = FMath::Clamp(CurrentStamina + 1, MinStamina, MaxStamina);
	UE_LOG(LogTemp, Warning, TEXT("Regenerated stamina! CurrentStamina: %f"), this->CurrentStamina);

	if (CurrentStamina == MaxStamina)
	{
		this->GetOwner()->GetWorldTimerManager().ClearTimer(this->RegenerateStaminaTimerHandle);
	}
}

void UMovement::StartCrouch()
{
	this->GetOwner()->GetWorldTimerManager().ClearTimer(this->DepleteStaminaTimerHandle);

	SetPlayerMaxWalkSpeed(this->CrouchSpeed);
	Cast<AL1Character>(PlayerRef)->ShortenPlayerCapsule();
	bIsCrouched = true;
}

void UMovement::StopCrouch()
{
	SetPlayerMaxWalkSpeed(this->WalkSpeed);
	Cast<AL1Character>(PlayerRef)->LengthenPlayerCapsule();
	bIsCrouched = false;
}

float UMovement::GetCrouchHalfHeight()
{
	return this->CrouchHalfHeight;
}

bool UMovement::IsCrouched()
{
	return bIsCrouched;
}
