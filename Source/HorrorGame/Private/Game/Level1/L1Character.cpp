// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Level1/L1Character.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Game/HGPlayerController.h"


// Sets default values
AL1Character::AL1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(this->RootComponent);
}

// Called when the game starts or when spawned
void AL1Character::BeginPlay()
{
	Super::BeginPlay();

	HGPlayerController = this->GetController<AHGPlayerController>();
}

// Called every frame
void AL1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	}
}

void AL1Character::LookRight(const FInputActionInstance& Instance)
{
	float Value =  Instance.GetValue().Get<float>();
	// UE_LOG(LogTemp, Warning, TEXT("LookRight value: %f"), Value);

	this->AddControllerYawInput(Value * HGPlayerController->GetLookSensitivity());
}

void AL1Character::LookUp(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();
	// UE_LOG(LogTemp, Warning, TEXT("LookUp value: %f"), Value);

	this->AddControllerPitchInput(Value * HGPlayerController->GetLookSensitivity());
}

