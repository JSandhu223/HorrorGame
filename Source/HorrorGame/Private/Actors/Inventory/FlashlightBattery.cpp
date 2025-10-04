// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Inventory/FlashlightBattery.h"


AFlashlightBattery::AFlashlightBattery()
{
	ItemData.ItemName = FName(TEXT("Flashlight Battery"));
	// NOTE: ItemData.Icon will be set in the blueprint class
	ItemData.MaxStackAmount = 8;
	ItemData.bCanBeUsed = true;
}
