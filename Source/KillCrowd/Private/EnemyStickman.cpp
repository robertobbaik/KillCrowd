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
		float Duration = AttackAnim->GetPlayLength();

		FTimerHandle TimerHandle;

		GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			//AIController->StartChasing();
		},
		Duration,
		false);
	}
}

void AEnemyStickman::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("StickMan Death"));
	// bIsAlive = false;
	// AIController->Death();
	// if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	// {
	// 	float Duration = DeathAnim->GetPlayLength();
	// 	
	// 	FTimerHandle TimerHandle;
	// 	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
	// 	{
	// 		SetActive(false);
	// 	}, Duration + 0.2f, false);
	// }
}

void AEnemyStickman::Operation()
{
	//AIController->StartChasing();
}
