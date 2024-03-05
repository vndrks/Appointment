// Fill out your copyright notice in the Description page of Project Settings.


#include "AppointmentAttributeSet.h"
#include "../Character/ACharacterBase.h"

UAppointmentAttributeSet::UAppointmentAttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
{
}

void UAppointmentAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	/** This is called whenever attributes change, so for max health/mana we want to scale the current totals to match */
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UAppointmentAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UAppointmentAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UAppointmentAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	/** Checks whether an instance of the ability system component exists. There must always be an instance. */
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UAppointmentAttributeSet::OnRep_Health()
{
	//GAMEPLAYATTRIBUTE_REPNOTIFY(UAppointmentAttributeSet, Health);
}

void UAppointmentAttributeSet::OnRep_MaxHealth()
{
	//GAMEPLAYATTRIBUTE_REPNOTIFY(UAppointmentAttributeSet, MaxHealth);
}
