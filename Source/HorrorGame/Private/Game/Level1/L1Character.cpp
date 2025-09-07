// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Level1/L1Character.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Game/HGPlayerController.h"
#include "Actors/InteractableActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/Movement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UMG/MainHUD.h"
#include "Blueprint/UserWidget.h"
#include "Actors/Grabbable/PhysicsDoor.h"
#include "Interfaces/Interactable.h"
#include "Interfaces/Grabbable.h"


// Sets default values
AL1Character::AL1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

	bFlashlightOn = false;
	bIsCrouched = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(this->RootComponent);
	Camera->SetWorldLocation(FVector(0.0f, 0.0f, 60.0f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Camera);
	SpringArm->TargetArmLength = 10.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, -30.0f);
	SpringArm->bEnableCameraRotationLag = 1;
	SpringArm->CameraRotationLagSpeed = 15.0f;

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	SpotLight->SetupAttachment(SpringArm);
	SpotLight->SetVisibility(bFlashlightOn);

	CharacterMovementComp = GetComponentByClass<UCharacterMovementComponent>();
	CharacterMovementComp->MaxWalkSpeed = 600.0f;

	MovementComp = CreateDefaultSubobject<UMovement>(TEXT("Movement"));

	CrouchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrouchTimeline"));
}

// Called when the game starts or when spawned
void AL1Character::BeginPlay()
{
	Super::BeginPlay();

	HGPlayerController = this->GetController<AHGPlayerController>();

	MovementComp->Initialize(this);
	this->Initialize();
}

// Called every frame
void AL1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AL1Character::Initialize()
{
	if (IsValid(MainHUDClass))
	{
		MainHUDInstance = CreateWidget<UMainHUD>(GetWorld(), MainHUDClass);

		if (IsValid(MainHUDInstance))
		{
			MainHUDInstance->AddToViewport();
		}
	}
}

AActor* AL1Character::LineTrace(float Length, bool bDrawLine, FColor HitColor, FColor NoHitColor)
{
	FHitResult OutHit;
	FVector TraceStart = Camera->GetComponentLocation();
	FVector TraceEnd = TraceStart + (Camera->GetForwardVector() * Length);
	GetWorld()->LineTraceSingleByChannel(
		OutHit,
		TraceStart,
		TraceEnd,
		ECollisionChannel::ECC_Visibility
	);

	if (bDrawLine)
	{
		DrawDebugLine(
			GetWorld(),
			TraceStart,
			TraceEnd,
			OutHit.bBlockingHit ? HitColor : NoHitColor,
			false,
			5.0f,
			0,
			0.25f
		);
	}

	return OutHit.GetActor();
}

// Called to bind functionality to input
void AL1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(LookRightAction, ETriggerEvent::Triggered, this, &AL1Character::LookRight);
		EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AL1Character::LookUp);
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AL1Character::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AL1Character::MoveRight);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AL1Character::_Jump);
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Started, this, &AL1Character::Use);
		EnhancedInputComponent->BindAction(FlashlightAction, ETriggerEvent::Started, this, &AL1Character::Flashlight);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AL1Character::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AL1Character::StopSprint);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AL1Character::_Crouch);
	}
}

void AL1Character::LookRight(const FInputActionInstance& Instance)
{
	float Value =  Instance.GetValue().Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("LookRight value: %f"), Value);

	this->AddControllerYawInput(Value * HGPlayerController->GetLookSensitivity());
}

void AL1Character::LookUp(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("LookUp value: %f"), Value);

	this->AddControllerPitchInput(Value * HGPlayerController->GetLookSensitivity());
}

void AL1Character::MoveForward(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("MoveForward value: %f"), Value);

	// We want the forward and backward movement to be independent of the player's yaw (z-axis direction).
	// Get the actor's forward vector, zero out the Z component, and normalize.
	// This ensures the character's does not move slower when they walk while looking up or down.
	FVector Forward = this->GetActorForwardVector();
	Forward.Z = 0.0f;
	Forward.Normalize();
	this->AddMovementInput(Forward, Value);
}

void AL1Character::MoveRight(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("MoveRight value: %f"), Value);

	this->AddMovementInput(this->GetActorRightVector(), Value);
	FVector Result = GetActorRightVector() * Value;
}

void AL1Character::_Jump(const FInputActionInstance& Instance)
{
	Jump();
}

void AL1Character::Use(const FInputActionInstance& Instance)
{
	AActor* HitActor = LineTrace(350.0f, true, FColor::Green, FColor::Red);
	if (IsValid(HitActor))
	{
		if (HitActor->Implements<UInteractable>())
		{
			AInteractableActor* InteractableActor = Cast<AInteractableActor>(HitActor);
			if (IsValid(InteractableActor))
			{
				InteractableActor->Interact();
			}
			return;
		}

		if (HitActor->Implements<UGrabbable>())
		{
			if (APhysicsDoor* PhysicsDoor = Cast<APhysicsDoor>(HitActor))
			{
				PhysicsDoor->GrabObject();
			}
		}
	}
}

void AL1Character::Flashlight(const FInputActionInstance& Instance)
{
	/*if (!bFlashlightOn)
	{
		SpotLight->SetVisibility(true);
		bFlashlightOn = true;
		UE_LOG(LogTemp, Warning, TEXT("Flashlight on"));
	}

	else
	{
		SpotLight->SetVisibility(false);
		bFlashlightOn = false;
		UE_LOG(LogTemp, Warning, TEXT("Flashlight off"));
	}*/

	// Equivalent code
	SpotLight->SetVisibility(bFlashlightOn = !bFlashlightOn);
}

void AL1Character::Sprint(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("Sprint key pressed"));

	MovementComp->StartSprint();
}

void AL1Character::StopSprint(const FInputActionInstance& Instance)
{
	UE_LOG(LogTemp, Warning, TEXT("Sprint key released"));

	MovementComp->StopSprint();
}

void AL1Character::_Crouch(const FInputActionInstance& Instance)
{
	if (!bIsCrouched)
	{
		UE_LOG(LogTemp, Warning, TEXT("Crouched"));
		MovementComp->StartCrouch();
		bIsCrouched = true;
	}
	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Uncrouched"));
		MovementComp->StopCrouch();
		bIsCrouched = false;
	}
}
