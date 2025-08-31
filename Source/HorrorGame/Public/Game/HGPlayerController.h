// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HORRORGAME_API AHGPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* PlayerContext;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

};
