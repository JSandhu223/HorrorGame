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

	struct FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)
	float SprintSpeed;

	UPROPERTY(EditAnywhere)
	float WalkSpeed;

	UPROPERTY(EditAnywhere)
	float MaxStamina;

	UPROPERTY(EditAnywhere)
	float MinStamina;

	float CurrentStamina;

private:
	void StartSprint();

	void StopSprint();

	void SetPlayerMaxWalkSpeed(float MaxWalkSpeed);

	// Called by our timer
	void SprintTimer();

public:	
	// Sets default values for this component's properties
	UMovement();

	void Initialize(class ACharacter* Character);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
