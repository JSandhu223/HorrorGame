// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventorySlot.h"
#include "Game/Level1/L1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InventoryComponent.h"
#include "Components/Image.h"
#include "Structs/InventoryItems.h"


void UInventorySlot::InitializeInventorySlot()
{
	PlayerRef = Cast<AL1Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void UInventorySlot::UpdateSlot()
{
	AInventoryItem* Item = PlayerRef->GetInventoryComp()->GetItemAtIndex(this->Index).Item.GetDefaultObject();
	UTexture2D* ItemIcon = Item->GetItemData().Icon;
	this->SlotImage->SetBrushFromTexture(ItemIcon, true);
}
