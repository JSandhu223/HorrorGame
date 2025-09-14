// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/ItemData.h"
#include "InventoryItem.generated.h"

UCLASS()
class HORRORGAME_API AInventoryItem : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FItemData ItemData;
	
public:	
	// Sets default values for this actor's properties
	AInventoryItem();

	FItemData GetItemData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
