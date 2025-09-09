// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Inventory/InventoryGrid.h"
#include "Game/HGPlayerController.h"
#include "Kismet/GameplayStatics.h"


void UInventoryGrid::NativePreConstruct()
{
	AHGPlayerController* PlayerController = Cast<AHGPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
