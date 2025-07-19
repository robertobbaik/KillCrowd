// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCrowdGameState.h"

#include "CharacterController.h"
#include "KillCrowdGameMode.h"
#include "Kismet/GameplayStatics.h"

void AKillCrowdGameState::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("GameState Start"));
	RemainTime = 600.f;
	bIsGameStarted = true;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AKillCrowdGameState::CountDown, 1.f, true);
}

void AKillCrowdGameState::CountDown()
{
	UE_LOG(LogTemp, Warning, TEXT("GameState CountDown"));
	RemainTime -= 1;

	UE_LOG(LogTemp, Warning, TEXT("%s"), *FormatTime(RemainTime));
	CharacterController->TimerText->SetText(FText::FromString(*FormatTime(RemainTime)));
}

void AKillCrowdGameState::EndGame()
{
}

FString AKillCrowdGameState::FormatTime(float Time)
{
	int32 Minutes = FMath::FloorToInt(Time / 60.0f);
	int32 Seconds = FMath::FloorToInt(Time) % 60;

	return FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
}

void AKillCrowdGameState::BeginPlay()
{
	Super::BeginPlay();
	//AKillCrowdGameMode* GameMode = AKillCrowdGameMode::GetInstance();
	CharacterController = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// void AKillCrowdGameState::Tick(float DeltaSeconds)
// {
// 	Super::Tick(DeltaSeconds);
// 	UE_LOG(LogTemp, Warning, TEXT("GameState Tick"));
// 	if (bIsGameStarted)
// 	{
// 		float RemainTime = GetWorldTimerManager().GetTimerRemaining(TimerHandle);
//
// 		UE_LOG(LogTemp, Warning, TEXT("%s"), *FormatTime(RemainTime));
// 		CharacterController->TimerText->SetText(FText::FromString(*FormatTime(RemainTime)));
// 	}
// }
