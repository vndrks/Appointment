// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "../Widgets/NPCUserWidget.h"
#include "../Abilities/GameAbilitySystemComponent.h"
#include "../Abilities/AppointmentGameplayAbility.h"
#include "../Abilities/AppointmentAttributeSet.h"
#include "ACharacterBase.generated.h"

UCLASS()
class APPOINTMENT_API AACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other
	//	, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation
	//	, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	UAppointmentAttributeSet* AttributeSet;

	// Friended to allow access to handle functions above
	friend UAppointmentAttributeSet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	/**
	 * Attempts to activate all abilities that match the specified tags
	 * Returns true if it thinks it activated, but it may return false positives due to failure later in activation.
	 * If bAllowRemoteActivation is true, it will remotely activate local/server abilities, if false it will only try to locally activate the ability
	 */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation = true);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UAppointmentGameplayAbility*>& ActiveAbilities);

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

	UPROPERTY()
	UGameAbilitySystemComponent* AbilitySystemComponent;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AACharacterBase* InstigatorCharacter, AActor* DamageCauser);


private:
	void	UpdateWidgetLocation();
	void	OnMouseClick();

	//void	OnMoveRight();
	//void	OnMoveLeft();
	//void	OnMoveBack();
	//void	OnJump();
	void	ShowNPCName();
//	FString GetName();

	FVector WidgetOffset;
	
};
