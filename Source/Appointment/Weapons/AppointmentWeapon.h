// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../AppointmentCharacter.h"
#include "AppointmentWeapon.generated.h"

UCLASS()
class APPOINTMENT_API AAppointmentWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAppointmentWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AAppointmentCharacter* MyPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetOwingPawn(AAppointmentCharacter* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const AAppointmentWeapon* LastWeapon);
	void OnUnEquip();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UStaticMeshComponent* WeaponMeshComponent;

	
};
