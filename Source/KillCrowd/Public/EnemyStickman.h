// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemyCharacter.h"
#include "EnemyStickman.generated.h"

/**
 * 
 */
UCLASS()
class KILLCROWD_API AEnemyStickman : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	virtual void Initialize(const FEnemyStats& EnemyStats) override;
	virtual void Attack() override;
	virtual void Death() override;
	virtual void Operation() override;

protected:
	
};
