// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacterNPC.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/TextBlock.h"


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

	
	NPCUserWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NPCUserWidget"));
	NPCUserWidgetComponent->SetupAttachment(RootComponent);
	NPCUserWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	NPCUserWidgetComponent->SetDrawSize(FVector2D(150.f, 30.f));
	NPCUserWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 300.f));

	static ConstructorHelpers::FClassFinder<UUserWidget> SpeechBubbleWidgetClassFinder(TEXT(
		"/Game/Widgets/BP_NPCUserWidget"));
	NPCUserWidgetClass = SpeechBubbleWidgetClassFinder.Class;

	NPCNameComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NPCNameWidget"));
	NPCNameComponent->SetupAttachment(RootComponent);
	NPCNameComponent->SetWidgetSpace(EWidgetSpace::Screen);
	NPCNameComponent->SetDrawSize(FVector2D(150.f, 30.f));
	NPCNameComponent->SetRelativeLocation(FVector(0.f, 0.f, 140.f));

	static ConstructorHelpers::FClassFinder<UUserWidget> NPCNameWidgetClassFinder(TEXT(
		"/Game/Widgets/BP_NPCNameWidget"));
	NPCNameWidgetClass = NPCNameWidgetClassFinder.Class;
}

// Called when the game starts or when spawned
void AACharacterNPC::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using ACharacterNPC"));

	if (NPCUserWidgetClass)
	{
		NPCUserWidgetComponent->SetWidgetClass(NPCUserWidgetClass);

		NPCUserWidgetObject = Cast<UNPCUserWidget>(NPCUserWidgetComponent->GetUserWidgetObject());

		if (NPCUserWidgetObject)
			NPCUserWidgetObject->SetPlainText();
	}
		

	if (NPCNameWidgetClass)
	{
		NPCNameComponent->SetWidgetClass(NPCNameWidgetClass);
		
		// Get Widget Object
		UUserWidget *NPCNameWidgetObject = Cast<UUserWidget>(NPCNameComponent->GetUserWidgetObject());
		UTextBlock* NPCNameTextBlock = Cast<UTextBlock>(NPCNameWidgetObject->GetWidgetFromName(FName("NPC_NAME_TEXT")));

		if (NPCNameTextBlock)
			NPCNameTextBlock->SetText(FText::FromString(ShownName));
	}
		

	WidgetOffset = FVector(10.0f, 10.0f, 10.0f);
	// UpdateWidgetLocation();
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

void AACharacterNPC::UpdateWidgetLocation()
{
	FVector ForwardVector = GetActorForwardVector();
	FVector ActorLocation = GetActorLocation();
	FVector WidgetLocation = GetActorLocation() + ForwardVector * WidgetOffset;

	if (NPCUserWidgetComponent)
	{
		// NPCUserWidgetComponent->SetWorldLocation(WidgetLocation);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("##### NPCUserWidgetComponent is Enabled #####"));
	}
}

void AACharacterNPC::OnMouseClick()
{
	UE_LOG(LogTemp, Log, TEXT("##### OnClick 111 #####"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("##### OnClick 222 #####"));
}

void AACharacterNPC::ShowNPCName()
{
	// NPCNameComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PlayerName"));
}

// Below Name is the last token on ItemLabel on UnrealEditor. (e,g, BP_ACharacterNPC_Emily -> Name : Emily)
//FString AACharacterNPC::GetName()
//{
//	FString AAFDName = GetFName().ToString();
//	//FString Label = GetActorLabel();
//	TArray<FString> SplitStrings;
//	AAFDName.ParseIntoArray(SplitStrings, TEXT("_"), true);
//
//	return SplitStrings.Last();
//}

