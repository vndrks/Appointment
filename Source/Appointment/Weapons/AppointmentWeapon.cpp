// Fill out your copyright notice in the Description page of Project Settings.


#include "AppointmentWeapon.h"

// Sets default values
AAppointmentWeapon::AAppointmentWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComponent->CastShadow = true;
	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMeshComponent;
}

// Called when the game starts or when spawned
void AAppointmentWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAppointmentWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAppointmentWeapon::SetOwingPawn(AAppointmentCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void AAppointmentWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();

		AttachToComponent(PawnMesh, FAttachmentTransformRules::KeepRelativeTransform);
		// Attach the SubObject to the RootComponent of this actor
		if (WeaponMeshComponent)
		{
			WeaponMeshComponent->AttachToComponent(PawnMesh, FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

void AAppointmentWeapon::OnEquip(const AAppointmentWeapon* LastWeapon)
{
	AttachMeshToPawn();
}

void AAppointmentWeapon::OnUnEquip()
{
	// WeaponMeshComponent->DetachFromParent();
}

