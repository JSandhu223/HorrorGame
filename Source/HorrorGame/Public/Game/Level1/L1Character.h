// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "L1Character.generated.h"


UCLASS()
class HORRORGAME_API AL1Character : public ACharacter
{
	GENERATED_BODY()

/////////// TIMELINE ///////////////////////////
private:
	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* CrouchTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat* CrouchTimelineFloatCurve;

	UFUNCTION()
	void UpdateCrouchTimeline(float Output);
////////////////////////////////////////////////

private:
	bool bFlashlightOn;

	// This will point to the default capsule component provided with our character
	class UCapsuleComponent* CapsuleComp;

	float OriginalCapsuleHalfHeight;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class USpotLightComponent* SpotLight;

	// This will point to the default character movement component on the Character class
	class UCharacterMovementComponent* CharacterMovementComp;

	// This is our custom movement component that will handle sprinting and crouching
	class UMovement* MovementComp;

	class AHGPlayerController* HGPlayerController;

	// This will be set to WBP_MainHUD in the editor
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UMainHUD> MainHUDClass;

	class UMainHUD* MainHUDInstance;

private:
	void Initialize();

	AActor* LineTrace(float Length, bool bDrawLine, FColor HitColor = FColor::White, FColor NoHitColor = FColor::White);

public:
	// Sets default values for this character's properties
	AL1Character();

	void ShortenPlayerCapsule();

	void LengthenPlayerCapsule();

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

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* FlashlightAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* CrouchAction;

	void LookRight(const struct FInputActionInstance& Instance);

	void LookUp(const struct FInputActionInstance& Instance);

	void MoveForward(const struct FInputActionInstance& Instance);

	void MoveRight(const struct FInputActionInstance& Instance);

	void _Jump(const struct FInputActionInstance& Instance);

	void Use(const struct FInputActionInstance& Instance);

	void Flashlight(const struct FInputActionInstance& Instance);

	void Sprint(const struct FInputActionInstance& Instance);
	void StopSprint(const struct FInputActionInstance& Instance);

	void _Crouch(const struct FInputActionInstance& Instance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
