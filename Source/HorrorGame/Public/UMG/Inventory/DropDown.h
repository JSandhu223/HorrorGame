// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropDown.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UDropDown : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class USizeBox* UseSection;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* ExamineSection;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* DropSection;

private:
	class AL1Character* PlayerRef;

	int32 SlotIndex;
	
protected:
	virtual void NativeConstruct() override;

public:
	void UpdateMenu(class UInventorySlot* InventorySlot);
};
