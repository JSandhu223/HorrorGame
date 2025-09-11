// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

USTRUCT()
struct FItemData
{
	GENERATED_BODY()

	FName* ItemName;
	UTexture2D* Icon;
};