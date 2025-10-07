// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/DropDown.h"
#include "UMG/Inventory/InventorySlot.h"
#include "Components/InventoryComponent.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Level1/L1Character.h"
#include "Actors/Inventory/InventoryItem.h"


void UDropDown::NativeConstruct()
{
	PlayerRef = Cast<AL1Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void UDropDown::UpdateMenu(UInventorySlot* InventorySlot)
{
	this->SlotIndex = InventorySlot->GetIndex();
	UE_LOG(LogTemp, Warning, TEXT("SlotIndex = %d"), SlotIndex);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerRef->GetInventoryComp()->GetName());
	FInventoryItems InventoryItem = PlayerRef->GetInventoryComp()->GetItemAtIndex(SlotIndex);
	UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *InventoryItem.Item->GetName());
	bool bCanUse = PlayerRef->GetInventoryComp()->GetItemAtIndex(SlotIndex).Item.GetDefaultObject()->GetItemData().bCanBeUsed;
	if (bCanUse)
	{
		this->UseSection->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		this->UseSection->SetVisibility(ESlateVisibility::Collapsed);
	}
}
