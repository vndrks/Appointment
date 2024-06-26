// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ApptInventoryShop.h"
#include "../Interface/InteractableInterface.h"
#include "ApptItem.generated.h"

UCLASS()
class APPOINTMENT_API AApptItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AApptItem();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "ITEM")
	class UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "ITEM")
	FItemData ItemData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class AAppointmentPlayerController* PlayerController) override;

	FItemData GetItemData() const { return ItemData; }

	virtual void Use(AAppointmentPlayerController* PlayerController) override;
};
