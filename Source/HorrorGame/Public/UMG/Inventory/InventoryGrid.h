// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGrid.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

private:
	// This will be set to WBP_InventorySlot from the editor
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventorySlot> InventorySlotBP;

	TArray<class UInventorySlot*> SlotsArray;

	int32 SlotsPerRow;

// THESE WIDGETS WILL BE BOUND TO THE WIDGETS CREATED IN THE BLUEPRINT CLASS
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UUniformGridPanel* InventoryGridPanel;

public:
	TArray<class UInventorySlot*>  GetSlotsArray();

protected:
	virtual void NativeConstruct() override;

};
