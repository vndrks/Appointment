// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacterNPC.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AACharacterNPC::AACharacterNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// AutoPossessPlayer = EAutoReceiveInput::Player0; // For Test Code

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_Quinn_NPC(
	//	TEXT("/Game/Character/Trooper/Mesh/Trooper_Lead.Trooper_Lead"));

	//USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();

	//if (SKM_Quinn_NPC.Succeeded() && SkeletalMeshComponent)
	//{
	//	SkeletalMeshComponent->SetSkeletalMesh(SKM_Quinn_NPC.Object);
	//}

	SpeechBubbleWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SpeechBubbleWidget"));
	SpeechBubbleWidgetComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT(
		"/Game/Widgets/BP_SpeechBubbleWidget"));
	
	WidgetClass = WidgetClassFinder.Class;	
}

// Called when the game starts or when spawned
void AACharacterNPC::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using ACharacterNPC"));
	}

	if (WidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("##### WidgetClass is Enabled"));
		SpeechBubbleWidgetComponent->SetWidgetClass(WidgetClass);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("##### WidgetClass is Disabled"));
	}

	WidgetOffset = FVector(100.0f, 0.0f, 0.0f);
	UpdateWidgetLocation();
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

void AACharacterNPC::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("##### OnClick 444 #####"));
}

// Called to bind functionality to input
void AACharacterNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("MouseClick", IE_Pressed, this, &AACharacterNPC::OnMouseClick);
}

void AACharacterNPC::OnMouseClick()
{
	UE_LOG(LogTemp, Log, TEXT("##### OnClick 111 #####"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("##### OnClick 222 #####"));
}

void AACharacterNPC::UpdateWidgetLocation()
{
	FVector ForwardVector = GetActorForwardVector();
	FVector WidgetLocation = GetActorLocation() + ForwardVector * WidgetOffset;

	if (SpeechBubbleWidgetComponent)
	{
		SpeechBubbleWidgetComponent->SetWorldLocation(WidgetLocation);
		UE_LOG(LogTemp, Log, TEXT("##### SpeechBubbleWidgetComponent is Enabled #####"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("##### SpeechBubbleWidgetComponent is Enabled #####"));
	}
}

