// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Inventory/InventoryItem.h"
#include "InventoryItems.generated.h"

USTRUCT()
struct FInventoryItems
{
	GENERATED_BODY()

	TSubclassOf<AInventoryItem> Item;
	int32 Amount;
};