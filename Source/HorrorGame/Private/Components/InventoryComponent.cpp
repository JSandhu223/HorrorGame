// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Game/HGPlayerController.h"
#include "UMG/Inventory/InventoryMenu.h"
#include "UMG/Inventory/InventoryGrid.h"
#include "UMG/Inventory/InventorySlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AHGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	// Initialize the array with default struct instances
	InventorySlots.Init(FInventoryItems(nullptr, 0), PlayerController->GetInventorySlots());
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::CheckForEmptySlot(int32& OutIndex)
{
	for (int32 i = 0; i < InventorySlots.Num(); i++)
	{
		if (!UKismetSystemLibrary::IsValidClass(InventorySlots[i].Item))
		{
			OutIndex = i;
			return true;
		}
	}

	// No empty slot was found
	OutIndex = -1;
	return false;
}

bool UInventoryComponent::CheckForFreeSlot(TSubclassOf<AInventoryItem> Item, int32& OutIndex)
{
	for (int32 i = 0; i < InventorySlots.Num(); i++)
	{
		if ((InventorySlots[i].Item == Item) && (InventorySlots[i].Amount < Item.GetDefaultObject()->GetItemData().MaxStackAmount))
		{
			OutIndex = i;
			return true;
		}
	}

	OutIndex = -1;
	return false;
}

// This gets called when the player collides with the collision sphere on the 'APickup' actor
bool UInventoryComponent::AddItem(TSubclassOf<AInventoryItem> Item, int32 Amount, int32& OutRemainder)
{
	int32 ItemMaxStackAmount = Item.GetDefaultObject()->GetItemData().MaxStackAmount;
	if (ItemMaxStackAmount > 1)
	{
		int32 OutIndex = 0;
		bool bFreeSlotFound = CheckForFreeSlot(Item, OutIndex);
		if (bFreeSlotFound)
		{
			int32 NewAmount = Amount + GetItemAtIndex(OutIndex).Amount;
			if (NewAmount <= ItemMaxStackAmount)
			{
				InventorySlots[OutIndex] = FInventoryItems(Item, NewAmount);
				UpdateInventorySlot(OutIndex);
				OutRemainder = 0;
				return true;
			}
			// If the amount to add exceeds the max stack amount, put the remaining number of items into the next available slot
			else
			{
				InventorySlots[OutIndex] = FInventoryItems(Item, ItemMaxStackAmount);
				UpdateInventorySlot(OutIndex);
				OutRemainder = 0;
				return AddItem(Item, NewAmount - ItemMaxStackAmount, OutRemainder);
				//return true;
			}
		}

		else
		{
			int32 OutIndex2 = 0;
			bool HasEmptySlot = CheckForEmptySlot(OutIndex2);
			if (!HasEmptySlot)
			{
				OutRemainder = Amount;
				return false;
			}
			else
			{
				if (Amount > ItemMaxStackAmount)
				{
					InventorySlots[OutIndex2] = FInventoryItems(Item, ItemMaxStackAmount);
					UpdateInventorySlot(OutIndex2);
					OutRemainder = 0;
					return AddItem(Item, Amount - ItemMaxStackAmount, OutRemainder);
					//return true
				}
				else
				{
					InventorySlots[OutIndex2] = FInventoryItems(Item, Amount);
					UpdateInventorySlot(OutIndex2);
					OutRemainder = 0;
					return true;
				}
			}
		}
	}

	// If the item can't be stacked
	else
	{
		int32 OutIndex = 0;
		bool HasEmptySlot = CheckForEmptySlot(OutIndex); // sets OutIndex to -1 if false
		if (!HasEmptySlot)
		{
			UE_LOG(LogTemp, Warning, TEXT("No slots available!"));
			OutRemainder = Amount;
			return false;
		}

		InventorySlots[OutIndex] = FInventoryItems(Item, 1);
		UpdateInventorySlot(OutIndex);

		OutRemainder = 0;
		return true;
	}
}

FInventoryItems UInventoryComponent::GetItemAtIndex(int32 Index)
{
	return InventorySlots[Index];
}

void UInventoryComponent::UpdateInventorySlot(int32 Index)
{
	TArray<UInventorySlot*> SlotsArray = PlayerController->GetInventoryMenuRef()->InventoryGridBP->GetSlotsArray();
	SlotsArray[Index]->UpdateSlot();
}
