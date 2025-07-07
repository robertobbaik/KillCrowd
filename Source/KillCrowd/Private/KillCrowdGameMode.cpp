// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCrowdGameMode.h"
#include "CharacterController.h"
#include "Kismet/GameplayStatics.h"


AKillCrowdGameMode::AKillCrowdGameMode()
{
	PlayerControllerClass = ACharacterController::StaticClass();
}

void AKillCrowdGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (ACharacterController* Controller = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		Controller->CreateCharacter();
	}

	PlayerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass()));
	
	FTimerHandle TimerHandle;

	GetWorldTimerManager().SetTimer(TimerHandle,this, &AKillCrowdGameMode::SpawnEnemyCharacter, 2.f, true);
}

void AKillCrowdGameMode::SpawnEnemyCharacter()
{
	float RandomAngle = FMath::RandRange(0.0f, 360.0f);
	float RandomDistance = FMath::RandRange(800.0f, 1000.0f);
    
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	float X = RandomDistance * FMath::Cos(FMath::DegreesToRadians(RandomAngle));
	float Y = RandomDistance * FMath::Sin(FMath::DegreesToRadians(RandomAngle));
    
	FVector SpawnLocation = PlayerLocation + FVector(X, Y, 0.0f);
	
	ABaseEnemyCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemyClass, SpawnLocation, FRotator(0,0,0));
	//SpawnedCharacter->Operation();
	if (SpawnedCharacter)
	{
		Enemies.Add(SpawnedCharacter);
	}
	
}
