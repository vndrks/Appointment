// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class APPOINTMENT_API UNPCUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UNPCUserWidget(const FObjectInitializer& ObjectInitializer);
	void SetPlainText();

private:
	UPROPERTY()
	class UTextBlock* NameTextBlock;
};
