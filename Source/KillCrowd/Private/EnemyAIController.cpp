// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BaseCharacter.h"
#include "BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"


const FName AEnemyAIController::PlayerKey = "Player";
const FName AEnemyAIController::AliveKey = "IsAlive";

AEnemyAIController::AEnemyAIController()
{
}

void AEnemyAIController::Initialize(const FEnemyStats& EnemyStats)
{
	BlackboardComp->SetValueAsFloat(TEXT("AttackCoolDown"), EnemyStats.AttackCoolDown);
	BlackboardComp->SetValueAsFloat(TEXT("AttackRange"), EnemyStats.AttackRange);
}

void AEnemyAIController::ResetAIState()
{
	if (BehaviorTree)
	{
		if (UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComp))
		{
			BlackboardComp = GetBlackboardComponent();
			AActor* TargetActor = Cast<AActor>(UGameplayStatics::GetActorOfClass(this, ABaseCharacter::StaticClass()));
			if (TargetActor)
			{
				BlackboardComp->SetValueAsObject(PlayerKey, TargetActor);
				BlackboardComp->SetValueAsBool(TEXT("IsAlive"), true);
				SetFocus(TargetActor);
			}
			
			RunBehaviorTree(BehaviorTree);
		}
	}
}

void AEnemyAIController::Death()
{
	ClearFocus(EAIFocusPriority::Gameplay);
	BlackboardComp->SetValueAsBool(AliveKey, false);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
