// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCUserWidget.h"
#include "Components/TextBlock.h"

UNPCUserWidget::UNPCUserWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UNPCUserWidget::SetPlainText()
{
	NameTextBlock = Cast<UTextBlock>(GetWidgetFromName(FName("NPC_NAME_TEXT")));
	
	if (NameTextBlock)
		NameTextBlock->SetText(FText::FromString("From NPCUserWidget Class"));
}
