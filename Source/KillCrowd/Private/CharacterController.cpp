// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "EnhancedInputComponent.h"
#include "BaseCharacter.h"
#include "EngineUtils.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerStart.h"

ACharacterController::ACharacterController() : InputMappingContext(nullptr), MoveAction(nullptr)
{
}

void ACharacterController::CreateCharacter()
{
	if (!IsLocalController()) return;
	APlayerStart* PlayerStart = nullptr;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		PlayerStart = *It;
		break;
	}

	if (!IsValid(PlayerStart)) return;
	
	if (UClass* LoadedClass = StaticLoadClass(ABaseCharacter::StaticClass(), nullptr,
		TEXT("/Game/02_Character/Blueprints/BP_Assassin.BP_Assassin_C")))
	{
		ABaseCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABaseCharacter>(LoadedClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
		Possess(SpawnedCharacter);
	}
}

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	if (HUDWidgetClass)
	{
		UUserWidget* HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("CharacterController BeginPlay"));
}



