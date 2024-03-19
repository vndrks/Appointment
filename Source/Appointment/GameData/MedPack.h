// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApptItem.h"
#include "MedPack.generated.h"

class AAppointmentPlayerController;

/**
 * 
 */
UCLASS()
class APPOINTMENT_API AMedPack : public AApptItem
{
	GENERATED_BODY()

public:
	AMedPack();

protected:
	UPROPERTY(EditAnywhere)
	float HealthValue;

public:
	virtual void Use(AAppointmentPlayerController* PlayerController) override;
	
};
