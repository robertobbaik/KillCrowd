// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "CharacterController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class KILLCROWD_API ACharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	ACharacterController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextBlock* TimerText;
	
	UFUNCTION()
	void CreateCharacter();
protected:
	virtual void BeginPlay() override;
};
