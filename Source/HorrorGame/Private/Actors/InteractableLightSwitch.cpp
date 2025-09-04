// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/InteractableLightSwitch.h"
#include "Engine/Light.h"
#include "Components/LightComponent.h"


void AInteractableLightSwitch::Interact()
{
	if (!IsValid(Light))
	{
		UE_LOG(LogTemp, Error, TEXT("%s: No Light is assigned to this light switch!"), *this->GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Interacted with light switch!"));

	ULightComponent* LightComp = Light->GetLightComponent();
	bool bIsLightOn = LightComp->GetVisibleFlag();
	// Toggle the light between on and off
	LightComp->SetVisibility(bIsLightOn = !bIsLightOn);
}
