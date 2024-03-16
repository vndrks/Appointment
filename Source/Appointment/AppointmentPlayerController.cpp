// Copyright Epic Games, Inc. All Rights Reserved.

#include "AppointmentPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "AppointmentCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Components/PawnComponent.h"
#include "Camera/CameraComponent.h"

#include "GameData/AppointmentItem.h"
#include "GameData/ApptItem.h"
#include "Input/AppointmentInputComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AAppointmentPlayerController::AAppointmentPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	bRightMouseClicked = false;
}

void AAppointmentPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	bEnableClickEvents = true;
}

void AAppointmentPlayerController::GetInventoryItems(TArray<UAppointmentItem*>& Items, FPrimaryAssetType ItemType)
{
	for (const TPair<UAppointmentItem*, FAppointmentItemData>& Pair : InventoryData)
	{
		if (Pair.Key)
		{
			FPrimaryAssetId AssetId = Pair.Key->GetPrimaryAssetId();

			// Filters based on item type
			if (AssetId.PrimaryAssetType == ItemType || ItemType.IsValid())
			{
				Items.Add(Pair.Key);
			}
		}
	}
}

void AAppointmentPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AAppointmentPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AAppointmentPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AAppointmentPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AAppointmentPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AAppointmentPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AAppointmentPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AAppointmentPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AAppointmentPlayerController::OnTouchReleased);

		// Setup custom event by Caspar
		EnhancedInputComponent->BindAction(SetKeyboardMoveAction, ETriggerEvent::Triggered, this, &AAppointmentPlayerController::InputMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started, this, &AAppointmentPlayerController::LookTest);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAppointmentPlayerController::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

	// 
	if (UAppointmentInputComponent* ApptInputComponent = Cast<UAppointmentInputComponent>(InputComponent))
	{
		// Setup Custom Event by Caspar
		// This is for Input Mapping within AppointmentCharacterComponent.
	}
}

void AAppointmentPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AAppointmentPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}

	// Test Code
	AActor* Actor = Hit.GetActor();
	if (Actor)
		UE_LOG(LogTemp, Log, TEXT("### Hit Actor(Mouse Left Click : %s"), *Actor->GetName());
	
	if (IInteractableInterface* Interface = Cast<IInteractableInterface>(Hit.GetActor()))
	{
		Interface->Interact(this);
	}
}

void AAppointmentPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AAppointmentPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AAppointmentPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AAppointmentPlayerController::InputMove(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	if (Value.X != 0.0f)
	{
		const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
		GetPawn()->AddMovementInput(MovementDirection, Value.X);
	}

	if (Value.Y != 0.0f)
	{
		const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		GetPawn()->AddMovementInput(MovementDirection, Value.Y);
	}
}

void AAppointmentPlayerController::LookTest(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisValue = InputActionValue.Get<FVector2D>();

	APawn* MainCharacter = GetPawn();

	InputActionValue.Get<FVector2D>();

	if (MainCharacter && bRightMouseClicked)
	{
		GetPawn()->AddControllerYawInput(LookAxisValue.X);
		GetPawn()->AddControllerPitchInput(LookAxisValue.Y);
	}
}

void AAppointmentPlayerController::PitchCamera(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, -1.0f);
}

void AAppointmentPlayerController::YawCamera(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, -1.0f);
}

void AAppointmentPlayerController::ZoomIn()
{
	bZoomingIn = true;
}

void AAppointmentPlayerController::ZoomOut()
{
	bZoomingIn = false;
}

void AAppointmentPlayerController::Interact(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Log, TEXT("##### Hit 0 #####"));
	APawn* ControlledPawn = GetPawn();
	AAppointmentCharacter* MainCharacter = Cast<AAppointmentCharacter>(ControlledPawn);
	if (MainCharacter)
	{
		UCameraComponent* CameraComponent = MainCharacter->GetTopDownCameraComponent();

		FVector Start = CameraComponent->GetComponentLocation();
		FVector End = Start + CameraComponent->GetForwardVector() * 4000.0f;

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
		{
			//AActor* Actor = HitResult.GetActor();
			//UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *Actor->GetName());

			if (IInteractableInterface* Interface = Cast<IInteractableInterface>(HitResult.GetActor()))
			{
				Interface->Interact(this);
			}
		}
	}
}
