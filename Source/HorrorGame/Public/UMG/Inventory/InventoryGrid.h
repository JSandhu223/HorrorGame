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

// THESE WIDGETS WILL BE BOUND TO THE WIDGETS CREATED IN THE BLUEPRINT CLASS
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UUniformGridPanel* InventoryGridPanel;

protected:
	virtual void NativeConstruct() override;

};
