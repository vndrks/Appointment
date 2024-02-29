// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Widgets/NPCUserWidget.h"
#include "ACharacterNPC.generated.h"

UCLASS()
class APPOINTMENT_API AACharacterNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacterNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other
	//	, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation
	//	, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnyWhere, Category = "Widgets")
	class UWidgetComponent* NPCUserWidgetComponent;

	UPROPERTY(VisibleAnyWhere, Category = "Widgets")
	class UWidgetComponent* NPCNameComponent;

	UPROPERTY(VisibleAnyWhere, Category = "Widget")
	class UNPCUserWidget* NPCUserWidgetObject;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> NPCUserWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> NPCNameWidgetClass;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "NPC")
	FString ShownName;

private:
	void	UpdateWidgetLocation();
	void	OnMouseClick();
	void	ShowNPCName();
//	FString GetName();

	FVector WidgetOffset;
	
};
