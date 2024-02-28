// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCPlayerController.h"

void ANPCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}
