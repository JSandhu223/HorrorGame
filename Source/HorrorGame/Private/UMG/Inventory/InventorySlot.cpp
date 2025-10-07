// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventorySlot.h"
#include "UMG/Inventory/InventoryMenu.h"
#include "Game/Level1/L1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/InventoryComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Internationalization/Text.h"
#include "Structs/InventoryItems.h"


void UInventorySlot::NativeConstruct()
{
	SlotButton->OnReleased.AddDynamic(this, &UInventorySlot::OnSlotButtonRelease);
}

// This gets called on 'NativeConstruct' for the InventoryMenu for each element in SlotsArray.
// Note that SlotsArray exists in the InventoryGrid class.
void UInventorySlot::InitializeInventorySlot(UInventoryMenu* InventoryMenu)
{
	PlayerRef = Cast<AL1Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	InventoryMenuRef = InventoryMenu;
	//UpdateSlot();
}

void UInventorySlot::UpdateSlot()
{
	TSubclassOf<AInventoryItem> ItemRef = PlayerRef->GetInventoryComp()->GetItemAtIndex(this->Index).Item;
	// Disable the inventory slot if there is no item in it
	if (!UKismetSystemLibrary::IsValidClass(ItemRef))
	{
		SlotButton->SetIsEnabled(false);
		SlotImage->SetBrushFromTexture(EmptyIcon, true);
		AmountText->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	// Enable the inventory slot when an item is added to it
	SlotButton->SetIsEnabled(true);

	AInventoryItem* Item = ItemRef.GetDefaultObject();
	UE_LOG(LogTemp, Warning, TEXT("UpdateSlot(): Index = %d"), this->Index);
	UTexture2D* ItemIcon = Item->GetItemData().Icon;
	this->SlotImage->SetBrushFromTexture(ItemIcon, true);

	int32 ItemAmount = PlayerRef->GetInventoryComp()->GetItemAtIndex(this->Index).Amount;
	FNumberFormattingOptions FormattingOptions;
	FormattingOptions.UseGrouping = true;
	FormattingOptions.MinimumIntegralDigits = 1;
	this->AmountText->SetText(FText::AsNumber(ItemAmount, &FormattingOptions));
	// Hide text if the player only has one of the item in their inventory
	ItemAmount <= 1 ? this->AmountText->SetVisibility(ESlateVisibility::Hidden): this->AmountText->SetVisibility(ESlateVisibility::Visible);
}

void UInventorySlot::SetRow(int RowToSet)
{
	this->Row = RowToSet;
}

int32 UInventorySlot::GetRow()
{
	return this->Row;
}

void UInventorySlot::SetColumn(int ColumnToSet)
{
	this->Column = ColumnToSet;
}

int32 UInventorySlot::GetColumn()
{
	return this->Column;
}

int32 UInventorySlot::GetIndex()
{
	return this->Index;
}

void UInventorySlot::SetIndex(int IndexToSet)
{
	this->Index = IndexToSet;
}

void UInventorySlot::OnSlotButtonRelease()
{
	TSubclassOf<AInventoryItem> ItemRef = PlayerRef->GetInventoryComp()->GetItemAtIndex(this->Index).Item;
	if (!UKismetSystemLibrary::IsValidClass(ItemRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot open drop down menu on empty inventory slot!"));
		return;
	}
	InventoryMenuRef->OpenDropDownMenu(this);
}
