// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventoryGrid.h"
#include "Game/HGPlayerController.h"
#include "Kismet/GameplayStatics.h"


void UInventoryGrid::NativeConstruct()
{
	Super::NativeConstruct();

	AHGPlayerController* PlayerController = Cast<AHGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	for (int32 i = 0; i < PlayerController->GetInventorySlots(); i++)
	{
		// Create widget of type UInventorySlot and store them in an array
	}
}
