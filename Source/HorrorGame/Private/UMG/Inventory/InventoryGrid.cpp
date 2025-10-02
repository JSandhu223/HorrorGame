// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventoryGrid.h"
#include "UMG/Inventory/InventorySlot.h"
#include "Game/HGPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/UniformGridPanel.h"


void UInventoryGrid::NativeConstruct()
{
	Super::NativeConstruct();

	SlotsPerRow = 4;

	AHGPlayerController* PlayerController = Cast<AHGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	for (int32 i = 0; i < PlayerController->GetInventorySlots(); i++)
	{
		// Create widget of type UInventorySlot and store them in an array
		UInventorySlot* SlotToAdd = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotBP);
		int32 Row = i / SlotsPerRow;
		int32 Column = i % SlotsPerRow;
		SlotToAdd->SetIndex(i); // possible REFACTOR: move this line to constructor in UInventorySlot
		SlotToAdd->SetRow(Row);
		SlotToAdd->SetColumn(Column);
		this->SlotsArray.Add(SlotToAdd);
		InventoryGridPanel->AddChildToUniformGrid(SlotToAdd, Row, Column);
		UE_LOG(LogTemp, Warning, TEXT("i = %d: %d, %d"), i, Row, Column);
	}
	//InventoryGridPanel->AddChildToUniformGrid(SlotsArray[0], 0, 0);

	//UE_LOG(LogTemp, Warning, TEXT("SlotsArray[0]: %s"), *SlotsArray[0]->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("SlotsArray length: %d"), SlotsArray.Num());
}

TArray<class UInventorySlot*> UInventoryGrid::GetSlotsArray()
{
	return this->SlotsArray;
}