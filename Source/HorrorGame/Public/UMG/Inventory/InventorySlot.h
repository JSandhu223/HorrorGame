// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemData.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* SizeBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* SlotButton;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOverlay* Overlay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* SlotImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* AmountText;

private:
	int32 Index;

	int32 Row;

	int32 Column;

	FItemData ItemData;

	int32 Amount;

	UPROPERTY(EditAnywhere)
	class UTexture2D* EmptyIcon;

private:
	class AL1Character* PlayerRef;

	class UInventoryMenu* InventoryMenuRef;

protected:
	virtual void NativeConstruct() override;

public:
	void InitializeInventorySlot(class UInventoryMenu* InventoryMenu);

	void UpdateSlot();

	void SetIndex(int IndexToSet);

	int32 GetIndex();

	void SetRow(int RowToSet);

	int32 GetRow();

	void SetColumn(int ColumnToSet);

	int32 GetColumn();

	UFUNCTION()
	void OnSlotButtonRelease();
};
