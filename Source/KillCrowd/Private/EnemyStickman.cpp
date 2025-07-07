// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStickman.h"

#include "EnemyAIController.h"

void AEnemyStickman::Initialize(const FEnemyStats& EnemyStats)
{
	
}

void AEnemyStickman::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("StickMan Attack"));
	if (AttackAnim)
	{
		PlayAnimMontage(AttackAnim);
		float Duration = AttackAnim->GetPlayLength();

		FTimerHandle TimerHandle;

		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			AIController->StartChasing();
		},
		Duration,
		false);
	}
}

void AEnemyStickman::Die()
{
	AIController->Death();
	PlayAnimMontage(DeathAnim);
}

void AEnemyStickman::Operation()
{
	//AIController->StartChasing();
}
