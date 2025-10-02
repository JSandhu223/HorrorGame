// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventoryMenu.h"
#include "UMG/Inventory/InventoryGrid.h"
#include "UMG/Inventory/InventorySlot.h"
#include "UMG/Inventory/DropDown.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/GridSlot.h"
#include "Components/UniformGridPanel.h"


void UInventoryMenu::NativeConstruct()
{
	TArray<UInventorySlot*> Slots = this->InventoryGridBP->GetSlotsArray();
	for (UInventorySlot* S : Slots)
	{
		S->InitializeInventorySlot(this);
	}
}

void UInventoryMenu::OpenDropDownMenu(UInventorySlot* InventorySlot)
{
	UE_LOG(LogTemp, Warning, TEXT("Called UInventoryMenu::OpenDropDownMenu"));
	UInventorySlot* GridSlot = Cast<UInventorySlot>(UWidgetLayoutLibrary::SlotAsGridSlot(InventorySlot));

	UE_LOG(LogTemp, Warning, TEXT("DesiredSize.X = %f, %d"), InventorySlot->GetDesiredSize().X, FMath::TruncToInt32(InventorySlot->GetDesiredSize().X));
	UE_LOG(LogTemp, Warning, TEXT("DesiredSize.Y = %f, %d"), InventorySlot->GetDesiredSize().Y, FMath::TruncToInt32(InventorySlot->GetDesiredSize().Y));
	// TODO: fix crash related to GridSlot
	//UE_LOG(LogTemp, Warning, TEXT("GridSlot = %s"), *GridSlot->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("GridSlot Row = %d"), GridSlot->Row);
	//UE_LOG(LogTemp, Warning, TEXT("GridSlot Column = %d"), GridSlot->Column);
	//UE_LOG(LogTemp, Warning, TEXT("New X = %d"), (GridSlot->Row + 1) * FMath::TruncToInt32(InventorySlot->GetDesiredSize().X));
	//UE_LOG(LogTemp, Warning, TEXT("New Y = %d"), (GridSlot->Column + 1) * FMath::TruncToInt32(InventorySlot->GetDesiredSize().Y));

	FMargin PaddingMargins = InventoryGridBP->InventoryGridPanel->GetSlotPadding();

	DropDownBP->SetRenderTranslation(
		FVector2D(
			((InventorySlot->GetColumn() + 0) * FMath::TruncToInt32(PaddingMargins.Left + PaddingMargins.Right + InventorySlot->GetDesiredSize().X)) + 10,
			((InventorySlot->GetRow() + 1) * FMath::TruncToInt32(PaddingMargins.Top + PaddingMargins.Bottom + InventorySlot->GetDesiredSize().Y)) - 10
		)
	);
	
}
