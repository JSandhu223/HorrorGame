// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventoryMenu.h"
#include "UMG/Inventory/InventoryGrid.h"
#include "UMG/Inventory/InventorySlot.h"


void UInventoryMenu::NativeConstruct()
{
	TArray<UInventorySlot*> Slots = this->InventoryGridBP->GetSlotsArray();
	for (UInventorySlot* S : Slots)
	{
		S->InitializeInventorySlot(this);
	}
}
