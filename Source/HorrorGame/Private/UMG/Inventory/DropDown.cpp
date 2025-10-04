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
	SlotIndex = InventorySlot->GetIndex();

	bool bCanUse = PlayerRef->GetInventoryComp()->GetItemAtIndex(SlotIndex).Item.GetDefaultObject()->GetItemData().bCanBeUsed;
	if (bCanUse)
	{
		this->UseSection->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		this->UseSection->SetVisibility(ESlateVisibility::Collapsed);
	}
}
