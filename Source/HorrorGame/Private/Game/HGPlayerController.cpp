// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HGPlayerController.h"
#include "EnhancedInputSubsystems.h"


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
