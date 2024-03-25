// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApptItem.h"
#include "Food.generated.h"

class AAppointmentPlayerController;
/**
 * 
 */
UCLASS()
class APPOINTMENT_API AFood : public AApptItem
{
	GENERATED_BODY()


 public:
	AFood();

protected:
	UPROPERTY(EditAnywhere)
	float RemoveFoodValue;

public:
	virtual void Use(AAppointmentPlayerController* PlayerController) override;

	
};
