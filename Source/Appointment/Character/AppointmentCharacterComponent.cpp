// Fill out your copyright notice in the Description page of Project Settings.


#include "AppointmentCharacterComponent.h"
#include "Engine/LocalPlayer.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "EnhancedInputSubsystems.h"
#include "../AppointmentPlayerController.h"
#include "../Input/AppointmentInputComponent.h"
#include "InputMappingContext.h"

UAppointmentCharacterComponent::UAppointmentCharacterComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UAppointmentCharacterComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	UE_LOG(LogTemp, Log, TEXT("##### Entry HandleChangeInitState #####"));

	APawn* Pawn = GetPawn<APawn>();

	if (AAppointmentPlayerController* PlayerController = GetController<AAppointmentPlayerController>())
	{
		UE_LOG(LogTemp, Log, TEXT("##### HandleChangeInitState Process 2 #####"));
		if (Pawn->InputComponent != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("##### HandleChangeInitState Process 3 #####"));
			InitializePlayerInput(Pawn->InputComponent);
		}
	}
}

void UAppointmentCharacterComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		UE_LOG(LogTemp, Log, TEXT("##### Pawn is False #####"));
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	
	const ULocalPlayer* LP = PC->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* SubSystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(SubSystem);

	SubSystem->ClearAllMappings();

	for (const FInputMappingContextAndPriority& Mapping : DefaultInputMappings)
	{
		// UInputMappingContext* IMC = Mapping.InputMapping.Get();
		if (UInputMappingContext* IMC = Mapping.InputMapping.Get())
		{
			if (Mapping.bRegisterWithSettings)
			{
				if (UEnhancedInputUserSettings* Settings = SubSystem->GetUserSettings())
				{
					Settings->RegisterInputMappingContext(IMC);
				}

				FModifyContextOptions Options = {};
				Options.bIgnoreAllPressedKeysUntilRelease = false;
				// Actually add the config to the local player							
				SubSystem->AddMappingContext(IMC, Mapping.Priority, Options);
			}
		}
	}

	// The Input Component has some additional functions to map Gameplay Tags to an Input Action.
	// If you want this functionality but still want to change your input component class, make it a subclass
	// of the AppointmentInputComponent or modify this component accordingly.
	UAppointmentInputComponent* ApptIC = Cast<UAppointmentInputComponent>(PlayerInputComponent);
	if (ensureMsgf(ApptIC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to ULyraInputComponent or a subclass of it.")))
	{
		// Add the key mappings that may have been set by the player
		// ApptIC->AddInputMappings(InputConfig, Subsystem);

	}
}
