// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventorySlot.h"
#include "Game/Level1/L1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InventoryComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Internationalization/Text.h"
#include "Structs/InventoryItems.h"


// This gets called on 'NativeConstruct' for the InventoryMenu for each element in SlotsArray.
// Note that SlotsArray exists in the InventoryGrid class.
void UInventorySlot::InitializeInventorySlot()
{
	PlayerRef = Cast<AL1Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void UInventorySlot::UpdateSlot()
{
	AInventoryItem* Item = PlayerRef->GetInventoryComp()->GetItemAtIndex(this->Index).Item.GetDefaultObject();
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

void UInventorySlot::SetIndex(int IndexToSet)
{
	this->Index = IndexToSet;
}