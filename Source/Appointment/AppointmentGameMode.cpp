// Copyright Epic Games, Inc. All Rights Reserved.

#include "AppointmentGameMode.h"
#include "AppointmentPlayerController.h"
#include "AppointmentCharacter.h"
#include "UObject/ConstructorHelpers.h"


AAppointmentGameMode::AAppointmentGameMode()
{
	// use our custom PlayerController class
	DefaultPawnClass = AAppointmentCharacter::StaticClass();
	PlayerControllerClass = AAppointmentPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
	//	TEXT("/Game/TopDown/Blueprints/BP_MainCharacter"));
	//if (PlayerPawnBPClass.Class != nullptr)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
	
	// set default controller to our Blueprinted controller
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
	//	TEXT("/Game/TopDown/Blueprints/BP_MainPlayerController"));
	//if(PlayerControllerBPClass.Class != NULL)
	//{
	//	PlayerControllerClass = PlayerControllerBPClass.Class;
	//}
}

void AAppointmentGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AAppointmentGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}
