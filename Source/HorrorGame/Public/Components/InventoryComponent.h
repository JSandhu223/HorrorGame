// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/InventoryItems.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TArray<FInventoryItems> InventorySlots;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	bool CheckForEmptySlot(int32& OutIndex);

	bool AddItem(TSubclassOf<AInventoryItem> Item, int32 Amount);

	FInventoryItems GetItemAtIndex(int32 Index);

	// Updates the widget
	void UpdateInventorySlot(int32 Index);

private:
	class AHGPlayerController* PlayerController;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
