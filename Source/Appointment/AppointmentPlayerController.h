// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "InputActionValue.h"
#include "./Interface/AppointmentInventoryInterface.h"
#include "AppointmentPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UAppointmentItem;
class AApptItem;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/** Experimental */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);

UCLASS()
class AAppointmentPlayerController : public APlayerController, public IAppointmentInventoryInterface
{
	GENERATED_BODY()

public:
	AAppointmentPlayerController();

	/** Map of all items owned by this player, from definition to data */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<UAppointmentItem*, FAppointmentItemData> InventoryData;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetKeyboardMoveAction;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Camera moving */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** This is used by the [WB_InventoryList] Blueprint */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void GetInventoryItems(TArray<UAppointmentItem*>& Items, FPrimaryAssetType ItemType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void InventoryItemChanged(bool bAdded, UAppointmentItem* item);

	void AddInventoryItem(FItemData ItemData);
	void AddHealth(float Value);
	void RemoveHunger(float Value);

	//UFUNCTION(Server, Reliable, WithValidation)
	//void Server_Interact(FVector Start, FVector End);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;
	
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	float Health;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	float Hunger;

	UPROPERTY(ReplicatedUsing = onRep_InventoryItems, Category = "Inventory")
	TArray<FItemData> InventoryItems;

	virtual void SetupInputComponent() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// To add mapping context
	virtual void BeginPlay();

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();
	void InputMove(const FInputActionValue& InputActionValue);
	void LookTest(const FInputActionValue& InputActionValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();

	void Interact(const FInputActionValue& InputActionValue);
	void Interact(FVector Start, FVector End);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(TSubclassOf<AApptItem> Item);

	UFUNCTION()
	void onRep_InventoryItems();

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void AddItemToInventoryWidget(FItemData ItemData);

	UFUNCTION(BlueprintNativeEvent, Category = "Inventory")
	void UpdateStates(float NewHunger, float NewfloatHealth);



private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	bool bRightMouseClicked;
};


