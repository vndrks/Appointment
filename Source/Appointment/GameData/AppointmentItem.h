// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AppointmentItem.generated.h"

class UAppointmentGameplayAbility;
/**
 * Base class for all items, do not blueprint directly
 */
UCLASS(Abstract, BlueprintType)
class APPOINTMENT_API UAppointmentItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UAppointmentItem(){}

	/** Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FPrimaryAssetType ItemType;

	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemName;
	
	
	/**  */
	/**  */
	/**  */
	/**  */

	
};
