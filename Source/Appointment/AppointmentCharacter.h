// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AppointmentCharacter.generated.h"

class AAppointmentWeapon;

UCLASS(Blueprintable)
class AAppointmentCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAppointmentCharacter();

protected:
	virtual void BeginPlay() override;

	void RotateCameraYaw(float AxisValue);

	void Interact();

	void SetCurrentWeapon(AAppointmentWeapon* NewWeapon, AAppointmentWeapon* LastWeapon);

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<TSubclassOf<AAppointmentWeapon>> DefaultInventoryClasses;

	void SpawnDefaultInventory();

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FName WeaponAttachPoint;
	
	TArray<AAppointmentWeapon*> Inventory;
	
	AAppointmentWeapon* CurrentWeapon;

public:
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	virtual void PostInitializeComponents() override;

	void OnMouseClick();
	void MoveForward(float AxisValue);
	USkeletalMeshComponent* GetSpecificPawnMesh() const;
	
	FName GetWeaponAttachPoint();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool IsDrinking;


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};