// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ApptInputDataAsset.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FApptInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * Non-mutable data asset that contains input configuration properties.
 */
UCLASS()
class APPOINTMENT_API UApptInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UApptInputDataAsset(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "MainCharacter|Pawn")
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

public:
	// List of input actions used by the owner. These input actions are mapped to a gameplay tag and must be manually bound.
	 UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	 TArray<FApptInputAction> NativeInputActions;
};
