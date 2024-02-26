// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacterNPC.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AACharacterNPC::AACharacterNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_Quinn_NPC(
	//	TEXT("/Game/Character/Trooper/Mesh/Trooper_Lead.Trooper_Lead"));

	//USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();

	//if (SKM_Quinn_NPC.Succeeded() && SkeletalMeshComponent)
	//{
	//	SkeletalMeshComponent->SetSkeletalMesh(SKM_Quinn_NPC.Object);
	//}
}

// Called when the game starts or when spawned
void AACharacterNPC::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using ACharacterNPC"));
	}
}

//void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other
//	, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation
//	, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
//{
//	UE_LOG(LogTemp, Log, TEXT("NotifyHit ---"));
//}

// Called every frame
void AACharacterNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AACharacterNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

