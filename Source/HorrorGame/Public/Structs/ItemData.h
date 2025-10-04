// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT()
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FName ItemName = FName("None");

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon = nullptr;

	UPROPERTY(VisibleAnywhere)
	int32 MaxStackAmount = 0;

	UPROPERTY(VisibleAnywhere)
	bool bCanBeUsed = true;
};