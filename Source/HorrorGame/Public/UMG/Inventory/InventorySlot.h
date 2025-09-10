// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
};
