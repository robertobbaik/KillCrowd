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
	UPROPERTY()
	TArray<ABaseEnemyCharacter*> Enemies;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Enemy")
	TSubclassOf<ABaseEnemyCharacter> EnemyClass;

	UPROPERTY()
	ABaseCharacter* PlayerCharacter;

	UFUNCTION()
	void SpawnEnemyCharacter();

};
