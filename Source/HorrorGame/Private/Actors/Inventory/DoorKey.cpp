// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Inventory/DoorKey.h"


ADoorKey::ADoorKey()
{
	ItemData.ItemName = FName(TEXT("Door Key"));
	// NOTE: ItemData.Icon will be set in the blueprint class
	ItemData.MaxStackAmount = 1;
	ItemData.bCanBeUsed = false;
}
