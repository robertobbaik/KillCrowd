// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BaseEnemyCharacter.h"
#include "GameFramework/GameMode.h"

#include "KillCrowdGameMode.generated.h"

/**
 * 
 */

UCLASS()
class KILLCROWD_API AKillCrowdGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AKillCrowdGameMode();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy")
	TArray<ABaseEnemyCharacter*> Enemies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy")
	TSet<ABaseEnemyCharacter*> AliveEnemyPool;

	
	UFUNCTION(BlueprintCallable, Category="Singleton")
	static AKillCrowdGameMode* GetInstance();
	
protected:
	virtual void BeginPlay() override;
	
	static AKillCrowdGameMode* Instance;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy")
	TSubclassOf<ABaseEnemyCharacter> EnemyClass;

	UPROPERTY()
	ABaseCharacter* PlayerCharacter;

	UFUNCTION()
	void SpawnEnemyCharacter();

public:
	UFUNCTION()
	void RemoveAlivePool(ABaseEnemyCharacter* EnemyCharacter);

	UFUNCTION()
	void ReturnEnemyPool(ABaseEnemyCharacter* EnemyCharacter);

	void RegisterConsoleCommands();
	
	UFUNCTION(BlueprintCallable, Category = "Enemy Data")
	bool LoadEnemyDataFromCSV();

	// 읽은 데이터 저장할 맵
	UPROPERTY(BlueprintReadOnly, Category = "Enemy Data")
	TMap<FString, FEnemyStats> EnemyDataMap;

private:
	// CSV 라인을 파싱하는 헬퍼 함수
	FEnemyStats ParseCSVLine(const FString& CSVLine);
};
