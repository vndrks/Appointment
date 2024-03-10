// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ApptPawnDataAsset.generated.h"

class UApptInputDataAsset;

/**
 * Appointment Pawn Data
 * 
 * Non-mutable data asset that contains properties used to define a pawn.
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "Main Character Pawn Data", ShortToolTip = "Data asset used to define a Pawn."))
class APPOINTMENT_API UApptPawnDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UApptPawnDataAsset(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MainCharacter|Pawn")
	TSubclassOf<APawn> PawnClass;

	// Class to instantiate for this pawn (should usually derive from ApptPawn or ApptCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MainCharacter|Pawn")
	TObjectPtr<UApptInputDataAsset> InputConfig;


	
};
