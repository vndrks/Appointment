// Fill out your copyright notice in the Description page of Project Settings.


#include "MedPack.h"
#include "../AppointmentPlayerController.h"

AMedPack::AMedPack()
{
	HealthValue = 10.0f;
}

void AMedPack::Use(AAppointmentPlayerController* PlayerController)
{
	PlayerController->AddHealth(HealthValue);
}
