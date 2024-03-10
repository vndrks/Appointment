// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "ApptInputDataAsset.h"
#include "AppointmentInputComponent.generated.h"

class UEnhancedInputLocalPlayerSubsystem;

/**
 * Component used to manage input mappings and bindings using an input config data asset.
 */
UCLASS(Config = Input)
class APPOINTMENT_API UAppointmentInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	UAppointmentInputComponent(const FObjectInitializer& ObjectInitializer);

	void AddInputMappings(const UApptInputDataAsset* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;

	template<class UserClass, typename FuncType>
	void BindNativeAction(const UApptInputDataAsset* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound);
};

template<class UserClass, typename FuncType>
void UAppointmentInputComponent::BindNativeAction(const UApptInputDataAsset* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig)
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}

}