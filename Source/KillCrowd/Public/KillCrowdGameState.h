// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "KillCrowdGameState.generated.h"

/**
 * 
 */

class ACharacterController;

UCLASS()
class KILLCROWD_API AKillCrowdGameState : public AGameState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	float RemainTime;

	UFUNCTION(BlueprintCallable, Category="Status")
	void StartGame();

	UFUNCTION()
	void CountDown();

	UFUNCTION(BlueprintCallable, Category="Status")
	void EndGame();
	
	UFUNCTION()
	FString FormatTime(float Time);
protected:
	FTimerHandle TimerHandle;

	UPROPERTY()
	bool bIsGameStarted = false;
	
	UPROPERTY(BlueprintReadOnly, Category="Status")
	ACharacterController* CharacterController;

	virtual void BeginPlay() override;
	//virtual void Tick(float DeltaSeconds) override;
};
