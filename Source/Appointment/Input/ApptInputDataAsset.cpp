// Fill out your copyright notice in the Description page of Project Settings.


#include "ApptInputDataAsset.h"

UApptInputDataAsset::UApptInputDataAsset(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UApptInputDataAsset::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FApptInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Log, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
