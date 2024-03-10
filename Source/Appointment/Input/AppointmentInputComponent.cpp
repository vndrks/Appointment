// Fill out your copyright notice in the Description page of Project Settings.


#include "AppointmentInputComponent.h"

#include "EnhancedInputSubsystems.h"

UAppointmentInputComponent::UAppointmentInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void UAppointmentInputComponent::AddInputMappings(const UApptInputDataAsset* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);
}

