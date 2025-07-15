// Fill out your copyright notice in the Description page of Project Settings.


#include "KillCrowdGameMode.h"
#include "CharacterController.h"
#include "Kismet/GameplayStatics.h"

AKillCrowdGameMode* AKillCrowdGameMode::Instance = nullptr;

AKillCrowdGameMode::AKillCrowdGameMode()
{
	PlayerControllerClass = ACharacterController::StaticClass();
	RegisterConsoleCommands();
	Instance = this;
}


AKillCrowdGameMode* AKillCrowdGameMode::GetInstance()
{
	return Instance;
}

void AKillCrowdGameMode::BeginPlay()
{
	Super::BeginPlay();
	Instance = this;
	if (ACharacterController* Controller = Cast<ACharacterController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		Controller->CreateCharacter();
	}

	PlayerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass()));
	
	FTimerHandle TimerHandle;
	
	GetWorldTimerManager().SetTimer(TimerHandle,this, &AKillCrowdGameMode::SpawnEnemyCharacter, 2.f, false);

}

void AKillCrowdGameMode::RemoveAlivePool(ABaseEnemyCharacter* EnemyCharacter)
{
	if (EnemyCharacter)
	{
		AliveEnemyPool.Remove(EnemyCharacter);
	}
}

void AKillCrowdGameMode::ReturnEnemyPool(ABaseEnemyCharacter* EnemyCharacter)
{
	if (EnemyCharacter)
	{
		Enemies.Push(EnemyCharacter);
	}
}

void AKillCrowdGameMode::RegisterConsoleCommands()
{
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("SpawnEnemy"),
		TEXT("Spawn a test enemy"),
		FConsoleCommandDelegate::CreateUObject(this, &AKillCrowdGameMode::SpawnEnemyCharacter),
		ECVF_Cheat
	);
}

bool AKillCrowdGameMode::LoadEnemyDataFromCSV()
{
	FString FilePath = FPaths::ProjectContentDir() + TEXT("Data/EnemyStats.csv");
    
	UE_LOG(LogTemp, Log, TEXT("Loading CSV file: %s"), *FilePath);
    
	// 파일 내용 읽기
	FString FileContent;
	if (!FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load CSV file: %s"), *FilePath);
		return false;
	}
    
	// 맵 초기화
	EnemyDataMap.Empty();
    
	// 줄별로 분할
	TArray<FString> Lines;
	FileContent.ParseIntoArrayLines(Lines);
    
	if (Lines.Num() <= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("CSV file is empty or only has header"));
		return false;
	}
    
	// 첫 번째 줄(헤더) 건너뛰고 데이터 처리
	for (int32 i = 1; i < Lines.Num(); i++)
	{
		if (Lines[i].IsEmpty())
		{
			continue;
		}
        
		// CSV 라인 분할
		TArray<FString> Values;
		Lines[i].ParseIntoArray(Values, TEXT(","), true);
        
		if (Values.Num() >= 7)
		{
			FString EnemyType = Values[0].TrimStartAndEnd();
			FEnemyStats Stats = ParseCSVLine(Lines[i]);
            
			EnemyDataMap.Add(EnemyType, Stats);
            
			UE_LOG(LogTemp, Log, TEXT("Loaded: %s (HP: %.1f, Damage: %.1f)"), 
				   *EnemyType, Stats.MaxHealth, Stats.AttackDamage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid line %d: %s"), i + 1, *Lines[i]);
		}
	}
    
	UE_LOG(LogTemp, Log, TEXT("Loaded %d enemy types total"), EnemyDataMap.Num());
	return EnemyDataMap.Num() > 0;
}

FEnemyStats AKillCrowdGameMode::ParseCSVLine(const FString& CSVLine)
{
	FEnemyStats Stats;
	TArray<FString> Values;
    
	CSVLine.ParseIntoArray(Values, TEXT(","), true);
    
	// CSV 형식: EnemyType,MaxHealth,AttackDamage,MovementSpeed,AttackRange,AttackCoolDown,ExperienceValue
	if (Values.Num() >= 7)
	{
		Stats.MaxHealth = FCString::Atof(*Values[1].TrimStartAndEnd());
		Stats.AttackDamage = FCString::Atof(*Values[2].TrimStartAndEnd());
		Stats.MovementSpeed = FCString::Atof(*Values[3].TrimStartAndEnd());
		Stats.AttackRange = FCString::Atof(*Values[4].TrimStartAndEnd());
		Stats.AttackCoolDown = FCString::Atof(*Values[5].TrimStartAndEnd());
		Stats.ExperienceValue = FCString::Atoi(*Values[6].TrimStartAndEnd());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid CSV format: %s"), *CSVLine);
		// 기본값 사용
		Stats = FEnemyStats();
	}
    
	return Stats;
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
