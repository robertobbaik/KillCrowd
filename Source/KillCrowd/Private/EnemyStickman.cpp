// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStickman.h"

#include "EnemyAIController.h"

void AEnemyStickman::Initialize(const FEnemyStats& EnemyStats)
{
	
}

void AEnemyStickman::Attack()
{
	if (!bIsAlive) return;
	UE_LOG(LogTemp, Warning, TEXT("StickMan Attack"));
	if (AttackAnim)
	{
		PlayAnimMontage(AttackAnim);
	}
}

void AEnemyStickman::Death()
{
	Super::Death();
	UE_LOG(LogTemp, Warning, TEXT("StickMan Death"));


}

void AEnemyStickman::Operation()
{
	
}
