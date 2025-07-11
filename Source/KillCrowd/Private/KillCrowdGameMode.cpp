// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCrowdGameMode.h"
#include "CharacterController.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
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
	
	GetWorldTimerManager().SetTimer(TimerHandle,this, &AKillCrowdGameMode::SpawnEnemyCharacter, 2.f, false);
	RegisterConsoleCommands();
}

void AKillCrowdGameMode::ReturnEnemyPool(ABaseEnemyCharacter* EnemyCharacter)
{
	if (EnemyCharacter)
	{
		AliveEnemyPool.Remove(EnemyCharacter);
		Enemies.Push(EnemyCharacter);
	}
}

void AKillCrowdGameMode::RegisterConsoleCommands()
{
	// 콘솔 명령어 등록
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("SpawnEnemy"),
		TEXT("Spawn a test enemy"),
		FConsoleCommandDelegate::CreateUObject(this, &AKillCrowdGameMode::SpawnEnemyCharacter),
		ECVF_Cheat
	);
    
	// IConsoleManager::Get().RegisterConsoleCommand(
	// 	TEXT("KillAll"),
	// 	TEXT("Kill all enemies"),
	// 	FConsoleCommandDelegate::CreateUObject(this, &AKillCrowdGameMode::KillAllEnemies),
	// 	ECVF_Cheat
	// );
}


void AKillCrowdGameMode::SpawnEnemyCharacter()
{
	float RandomAngle = FMath::RandRange(0.0f, 360.0f);
	float RandomDistance = FMath::RandRange(800.0f, 1000.0f);
    
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	float X = RandomDistance * FMath::Cos(FMath::DegreesToRadians(RandomAngle));
	float Y = RandomDistance * FMath::Sin(FMath::DegreesToRadians(RandomAngle));
    
	FVector SpawnLocation = PlayerLocation + FVector(X, Y, 0.0f);

	UE_LOG(LogTemp, Warning, TEXT("Enemie : %d "), Enemies.Num());
	UE_LOG(LogTemp, Warning, TEXT("Alive : %d "), AliveEnemyPool.Num());
	if (Enemies.Num() > 0)
	{
		if (ABaseEnemyCharacter* SpawnedCharacter = Enemies.Pop())
		{
			SpawnedCharacter->SetActorLocation(SpawnLocation);
			SpawnedCharacter->SetActive(true);
			AliveEnemyPool.Add(SpawnedCharacter);
		}
	}
	else
	{
		if (ABaseEnemyCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABaseEnemyCharacter>(EnemyClass, SpawnLocation, FRotator(0,0,0)))
		{
			SpawnedCharacter->SetActive(true);
		 	AliveEnemyPool.Add(SpawnedCharacter);
		}
	}
}
