// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/PrimaryAssetId.h"
#include "AppointmentCommonUtils.generated.h"

/** Struct representing a slot for an item, shown in the UI */
USTRUCT(BlueprintType)
struct APPOINTMENT_API FAppointmentItemSlot
{
	GENERATED_BODY()

	FAppointmentItemSlot() {}
};


/** Extra information about a AppointmentItem that is in a player's inventory */
USTRUCT(BlueprintType)
struct APPOINTMENT_API FAppointmentItemData
{
	GENERATED_BODY()

	FAppointmentItemData()
		: ItemCount(1), ItemLevel(1)
		{}

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemCount;

	/** This level of this item, This level is shared for all instances, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemLevel;

	/** Equality operators */
	bool operator==(const FAppointmentItemData& Other) const
	{
		return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel;
	}
};