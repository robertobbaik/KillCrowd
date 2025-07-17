// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "KillCrowdGameState.generated.h"

/**
 * 
 */
UCLASS()
class KILLCROWD_API AKillCrowdGameState : public AGameState
{
	GENERATED_BODY()
public:
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	// float RemainTime;

	UFUNCTION(BlueprintCallable, Category="Status")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category="Status")
	void EndGame();

	UFUNCTION()
	FString FormatTime(float RemainTime);
protected:
	FTimerHandle TimerHandle;

	virtual void Tick(float DeltaSeconds) override;
};
