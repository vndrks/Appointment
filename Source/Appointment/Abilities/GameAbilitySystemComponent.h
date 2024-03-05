// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AppointmentGameplayAbility.h"
#include "GameAbilitySystemComponent.generated.h"

class UAppointmentGameplayAbility;

/**
 * 
 */
UCLASS()
class APPOINTMENT_API UGameAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	// Constructor and overrides
	UGameAbilitySystemComponent();

	/** Returns a list of currently active ability instances that match the tags */
	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContatiner, TArray<UAppointmentGameplayAbility*>& ActiveAbilities);
};
