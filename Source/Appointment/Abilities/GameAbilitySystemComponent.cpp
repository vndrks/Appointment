// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbilitySystemComponent.h"

UGameAbilitySystemComponent::UGameAbilitySystemComponent()
{
}

void UGameAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContatiner, TArray<UAppointmentGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActive;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContatiner, AbilitiesToActive, false);

	for (FGameplayAbilitySpec* Spec : AbilitiesToActive)
	{
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<UAppointmentGameplayAbility>(ActiveAbility));
		}
	}
}
