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
const FName AEnemyAIController::AliveKey = "Alive";

AEnemyAIController::AEnemyAIController()
{
	
}

void AEnemyAIController::StopChasing()
{
	bIsChasing = false;
	StopMovement();
}

void AEnemyAIController::Death()
{
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

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	EnemyCharacter = Cast<ABaseEnemyCharacter>(GetPawn());
	EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	if (BehaviorTree)
	{
		if (UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComp))
		{
			BlackboardComp = GetBlackboardComponent();
			AActor* TargetActor = Cast<AActor>(UGameplayStatics::GetActorOfClass(this, ABaseCharacter::StaticClass()));
			if (TargetActor)
			{
				BlackboardComp->SetValueAsObject(PlayerKey, TargetActor);
			}
			
			
			RunBehaviorTree(BehaviorTree);
		}
	}
}

// UBlackboardComponent* AEnemyAIController::GetBlackboard() const
// {
// 	return Blackboard;
// }
