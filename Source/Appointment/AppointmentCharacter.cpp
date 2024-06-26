// Copyright Epic Games, Inc. All Rights Reserved.

#include "AppointmentCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "./Weapons/AppointmentWeapon.h"

AAppointmentCharacter::AAppointmentCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	// CameraBoom->TargetArmLength = 800.f;
	// CameraBoom->bEnableCameraLag = true;
	// CameraBoom->CameraLagSpeed = 3.0f;
	// CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	CameraBoom->CameraLagSpeed = 3.0f;

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	
	
}

void AAppointmentCharacter::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void AAppointmentCharacter::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void AAppointmentCharacter::PitchYawCamera(const FInputActionValue& InputActionValue)
{
	FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	CameraInput.Y = ActionValue.Y;
	CameraInput.X = ActionValue.X;
}

void AAppointmentCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	//액터의 요를 회전하며, 이에 따라 어태치된 카메라가 회전
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	//카메라의 피치를 회전하되 항상 아래를 보도록 제한
	{
		FRotator NewRotation = CameraBoom->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		CameraBoom->SetWorldRotation(NewRotation);
	}
}

void AAppointmentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MouseClick", IE_Pressed, this, &AAppointmentCharacter::OnMouseClick);
	
	
	// PlayerInputComponent->BindAxis("Interact", this, &AAppointmentCharacter::Interact);
	PlayerInputComponent->BindAxis("MoveForward", this, &AAppointmentCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RotateCameraYaw", this, &AAppointmentCharacter::RotateCameraYaw);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AAppointmentCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RotateCameraYaw", this, &AAppointmentCharacter::RotateCameraYaw);

	PlayerInputComponent->BindAxis("CameraPitch", this, &AAppointmentCharacter::PitchCamera);
	PlayerInputComponent->BindAxis("CameraYaw", this, &AAppointmentCharacter::YawCamera);
}

void AAppointmentCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpawnDefaultInventory();
}

void AAppointmentCharacter::OnMouseClick()
{
	UE_LOG(LogTemp, Log, TEXT("##### OnClick 7615 #####"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("##### OnClick #####"));
}

USkeletalMeshComponent* AAppointmentCharacter::GetSpecificPawnMesh() const
{
	return GetMesh();
}

FName AAppointmentCharacter::GetWeaponAttachPoint()
{
	return WeaponAttachPoint;
}

void AAppointmentCharacter::MoveForward(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();

		/** Create a rotation with only Yaw component, ignoring Pitch and Roll. */
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		/** Calculate the unit vector representing the forward direction of the character in world.  */
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
	}
}

void AAppointmentCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("I am Main Character."));
}

void AAppointmentCharacter::RotateCameraYaw(float AxisValue)
{
	UE_LOG(LogTemp, Log, TEXT("##### RotateCameraYaw"));
	AddActorWorldRotation(FRotator(0.0f, AxisValue, 0.0f));
}

void AAppointmentCharacter::Interact(const FInputActionValue& InputActionValue)
{
	FVector Start = TopDownCameraComponent->GetComponentLocation();
	FVector End = Start + TopDownCameraComponent->GetForwardVector() + 500.0f;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	UE_LOG(LogTemp, Log, TEXT("##### Hit Actor"));

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params))
	{
		if (AActor* Actor = HitResult.GetActor())
		{
			UE_LOG(LogTemp, Log, TEXT("##### Hit Actor"));
			// UE_LOG(LogTemp, Log, TEXT("##### Hit Actor : %s"), *Actor->GetName());
		}
	}
}

void AAppointmentCharacter::SetCurrentWeapon(AAppointmentWeapon* NewWeapon, AAppointmentWeapon* LastWeapon)
{
	AAppointmentWeapon* LocalLastWeapon = NULL;

	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != CurrentWeapon)
	{
		LocalLastWeapon = CurrentWeapon;
	}

	if (LocalLastWeapon)
	{
		LocalLastWeapon->OnUnEquip();
	}

	CurrentWeapon = NewWeapon;

	if (NewWeapon)
	{
		NewWeapon->SetOwingPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void AAppointmentCharacter::SpawnDefaultInventory()
{
	AAppointmentWeapon* NewWeapon;
	for (int32 i = 0; i < DefaultInventoryClasses.Num(); ++i)
	{
		if (DefaultInventoryClasses[i])
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			NewWeapon = GetWorld()->SpawnActor<AAppointmentWeapon>(DefaultInventoryClasses[i], SpawnParameters);

			if (NewWeapon)
			{
				Inventory.AddUnique(NewWeapon);
				SetCurrentWeapon(Inventory[0], CurrentWeapon);
			}
		}
	}

	//if (Inventory.Num() > 0)
	//{
	//	if (Inventory[0])
	//	{
	//		SetCurrentWeapon(Inventory[0], CurrentWeapon);
	//	}
	//}
}
