// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interactable.h"
#include "L1Character.generated.h"

UCLASS()
class HORRORGAME_API AL1Character : public ACharacter
{
	GENERATED_BODY()

private:
	class AHGPlayerController* HGPlayerController;

private:
	void Initialize();

	AActor* LineTrace(float Length, bool bDrawLine);

public:
	// Sets default values for this character's properties
	AL1Character();

// Input Actions
private:
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookRightAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookUpAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* UseAction;

	void LookRight(const struct FInputActionInstance& Instance);

	void LookUp(const struct FInputActionInstance& Instance);

	void MoveForward(const struct FInputActionInstance& Instance);

	void MoveRight(const struct FInputActionInstance& Instance);

	void _Jump(const struct FInputActionInstance& Instance);

	void Use(const struct FInputActionInstance& Instance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;

	// This will point to the default character movement component on the Character class
	class UCharacterMovementComponent* MovementComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
