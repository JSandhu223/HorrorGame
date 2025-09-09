// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HGPlayerController.h"
#include "EnhancedInputSubsystems.h"


AHGPlayerController::AHGPlayerController()
{
	LookSensitivity = 0.8f;
	InventorySlots = 8;
}

void AHGPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void AHGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (ULocalPlayer* LocalPlayer = this->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (PlayerContext)
			{
				Subsystem->AddMappingContext(PlayerContext, 0);
			}
		}
	}

}

float AHGPlayerController::GetLookSensitivity()
{
	return this->LookSensitivity;
}