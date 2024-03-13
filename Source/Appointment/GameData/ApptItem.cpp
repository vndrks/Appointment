// Fill out your copyright notice in the Description page of Project Settings.


#include "ApptItem.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AApptItem::AApptItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = ItemMesh;
}

// Called when the game starts or when spawned
void AApptItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AApptItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AApptItem::Interact()
{
	Destroy();
}

