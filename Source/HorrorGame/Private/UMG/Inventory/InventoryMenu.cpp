// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventoryMenu.h"
#include "UMG/Inventory/InventoryGrid.h"
#include "UMG/Inventory/InventorySlot.h"
#include "UMG/Inventory/DropDown.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/GridSlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UInventoryMenu::NativeConstruct()
{
	CloseDropDownMenuButton->OnPressed.AddDynamic(this, &UInventoryMenu::CloseDropDownMenu);

	TArray<UInventorySlot*> Slots = this->InventoryGridBP->GetSlotsArray();
	for (UInventorySlot* S : Slots)
	{
		S->InitializeInventorySlot(this);
	}
}

void UInventoryMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	CloseDropDownMenuButton->SetUserFocus(UGameplayStatics::GetPlayerController(this, 0));
}

void UInventoryMenu::OpenDropDownMenu(UInventorySlot* InventorySlot)
{
	// DEBUG
	UE_LOG(LogTemp, Warning, TEXT("Called UInventoryMenu::OpenDropDownMenu"));

	FMargin PaddingMargins = InventoryGridBP->InventoryGridPanel->GetSlotPadding();

	DropDownBP->SetRenderTranslation(
		FVector2D(
			((InventorySlot->GetColumn() + 0) * FMath::TruncToInt32(PaddingMargins.Left + PaddingMargins.Right + InventorySlot->GetDesiredSize().X)) + 10,
			((InventorySlot->GetRow() + 1) * FMath::TruncToInt32(PaddingMargins.Top + PaddingMargins.Bottom + InventorySlot->GetDesiredSize().Y)) - 10
		)
	);

	DropDownBP->UpdateMenu(InventorySlot);
	DropDownBP->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CloseDropDownMenuButton->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryMenu::CloseDropDownMenu()
{
	DropDownBP->SetVisibility(ESlateVisibility::Collapsed);
	CloseDropDownMenuButton->SetVisibility(ESlateVisibility::Collapsed);
}
