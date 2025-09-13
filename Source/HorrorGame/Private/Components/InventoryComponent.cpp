// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "Game/HGPlayerController.h"
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

	AHGPlayerController* PlayerController = Cast<AHGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
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

bool UInventoryComponent::AddItem(TSubclassOf<AInventoryItem> Item, int32 Amount)
{
	//Item->GetItemData().MaxStackAmount;
	Item.GetDefaultObject()->GetItemData().MaxStackAmount;

	int32 OutIndex = 0;
	bool HasEmptySlot = CheckForEmptySlot(OutIndex); // sets OutIndex to -1 if false
	if (!HasEmptySlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("No free slots!"));
		return false;
	}

	InventorySlots[OutIndex] = FInventoryItems(Item, Amount);
	return true;
}

FInventoryItems UInventoryComponent::GetItemAtIndex(int32 Index)
{
	return InventorySlots[Index];
}
