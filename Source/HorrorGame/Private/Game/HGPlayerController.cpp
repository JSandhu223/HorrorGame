// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/HGPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "UMG/Inventory/InventoryMenu.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


AHGPlayerController::AHGPlayerController()
{
	LookSensitivity = 0.8f;
	InventorySlots = 8;
	bIsInventoryOpen = false;
}

void AHGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InventoryMenuRef = CreateWidget<UInventoryMenu>(GetWorld(), InventoryMenuBP);
	InventoryMenuRef->SetVisibility(ESlateVisibility::Collapsed);
	InventoryMenuRef->AddToViewport();
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

void AHGPlayerController::ToggleInventory()
{
	if (!bIsInventoryOpen)
	{
		bIsInventoryOpen = true;

		// Disable character movment and camera movement
		UGameplayStatics::GetPlayerCharacter(this, 0)->GetCharacterMovement()->DisableMovement();
		this->SetIgnoreLookInput(true);

		this->SetShowMouseCursor(true);

		InventoryMenuRef->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		SetInputMode(FInputModeGameAndUI());
	}

	else
	{
		bIsInventoryOpen = false;

		// Enable character movment and camera movement
		UGameplayStatics::GetPlayerCharacter(this, 0)->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		this->ResetIgnoreLookInput();

		this->SetShowMouseCursor(false);

		InventoryMenuRef->SetVisibility(ESlateVisibility::Collapsed);

		SetInputMode(FInputModeGameOnly());
	}
}

float AHGPlayerController::GetLookSensitivity()
{
	return this->LookSensitivity;
}

int32 AHGPlayerController::GetInventorySlots()
{
	return this->InventorySlots;
}

bool AHGPlayerController::IsInventoryOpen()
{
	return this->bIsInventoryOpen;
}
