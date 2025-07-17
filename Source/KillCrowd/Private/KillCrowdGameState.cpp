// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCrowdGameState.h"
#include "KillCrowdGameMode.h"

void AKillCrowdGameState::StartGame()
{
	AKillCrowdGameMode* GameMode = AKillCrowdGameMode::GetInstance();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKillCrowdGameState::EndGame, 600.f, false);
}

void AKillCrowdGameState::EndGame()
{
}

FString AKillCrowdGameState::FormatTime(float RemainTime)
{
	int32 Minutes = FMath::FloorToInt(RemainTime / 60.0f);
	int32 Seconds = FMath::FloorToInt(RemainTime) % 60;
    
	return FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
}

void AKillCrowdGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float RemainTime = GetWorldTimerManager().GetTimerRemaining(TimerHandle);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *FormatTime(RemainTime));
}

