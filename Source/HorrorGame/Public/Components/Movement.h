// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Movement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORGAME_API UMovement : public UActorComponent
{
	GENERATED_BODY()

private:
	class ACharacter* PlayerRef;

	struct FTimerHandle DepleteStaminaTimerHandle;

	struct FTimerHandle RegenerateStaminaTimerHandle;

	UPROPERTY(EditAnywhere)
	float SprintSpeed;

	UPROPERTY(EditAnywhere)
	float WalkSpeed;

	UPROPERTY(EditAnywhere)
	float MaxStamina;

	UPROPERTY(EditAnywhere)
	float MinStamina;

	float CurrentStamina;

	float StaminaDepletionRate;

	float StaminaRegenRate;

	float CrouchSpeed;

	float CrouchHalfHeight;

public:	
	// Sets default values for this component's properties
	UMovement();

	void Initialize(class ACharacter* Character);

	void StartSprint();

	void StopSprint();

private:
	void SetPlayerMaxWalkSpeed(float MaxWalkSpeed);

	// Called by timer for depleting stamina
	void DepleteStamina();

	void RegenerateStamina();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
