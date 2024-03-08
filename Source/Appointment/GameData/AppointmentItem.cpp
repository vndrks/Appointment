// Fill out your copyright notice in the Description page of Project Settings.


#include "AppointmentItem.h"

FPrimaryAssetId UAppointmentItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}
