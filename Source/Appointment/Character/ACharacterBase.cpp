// Fill out your copyright notice in the Description page of Project Settings.


#include "ACharacterBase.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/TextBlock.h"


// Sets default values
AACharacterBase::AACharacterBase()
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

	/** Create Ability system Component, and set it to explicitly replicated */
	AbilitySystemComponent = CreateDefaultSubobject<UGameAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	/** Create the attribute set, this replicated by default */
	AttributeSet = CreateDefaultSubobject<UAppointmentAttributeSet>(TEXT("AttributeSet"));

}

// Called when the game starts or when spawned
void AACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using ACharacterBase"));

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
void AACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACharacterBase::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString("##### OnClick 444 #####"));
}

// Called to bind functionality to input
void AACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("MouseClick", IE_Pressed, this, &AACharacterBase::OnMouseClick);
}

UAbilitySystemComponent* AACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float AACharacterBase::GetHealth() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetHealth();
}

bool AACharacterBase::ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation)
{
	if (AbilitySystemComponent)
	{
		return AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags, bAllowRemoteActivation);
	}
	return false;
}

void AACharacterBase::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UAppointmentGameplayAbility*>& ActiveAbilities)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
	}
}

void AACharacterBase::UpdateWidgetLocation()
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

void AACharacterBase::OnMouseClick()
{
	UE_LOG(LogTemp, Log, TEXT("##### OnClick 111 #####"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("##### OnClick 222 #####"));
}

void AACharacterBase::ShowNPCName()
{
	// NPCNameComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PlayerName"));
}

// Below Name is the last token on ItemLabel on UnrealEditor. (e,g, BP_ACharacterNPC_Emily -> Name : Emily)
//FString AACharacterBase::GetName()
//{
//	FString AAFDName = GetFName().ToString();
//	//FString Label = GetActorLabel();
//	TArray<FString> SplitStrings;
//	AAFDName.ParseIntoArray(SplitStrings, TEXT("_"), true);
//
//	return SplitStrings.Last();
//}

