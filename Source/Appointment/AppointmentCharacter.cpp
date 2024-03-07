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
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AAppointmentCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AAppointmentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MouseClick", IE_Pressed, this, &AAppointmentCharacter::OnMouseClick);
}

void AAppointmentCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpawnDefaultInventory();
}

void AAppointmentCharacter::OnMouseClick()
{
	//UE_LOG(LogTemp, Log, TEXT("##### OnClick #####"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("##### OnClick #####"));
}

USkeletalMeshComponent* AAppointmentCharacter::GetSpecificPawnMesh() const
{
	return GetMesh();
}

FName AAppointmentCharacter::GetWeaponAttachPoint()
{
	return WeaponAttachPoint;
}

void AAppointmentCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("I am Main Character."));
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
