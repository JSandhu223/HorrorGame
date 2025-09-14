// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryMenu.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UInventoryGrid* InventoryGridBP;

protected:
	virtual void NativeConstruct() override;
};
