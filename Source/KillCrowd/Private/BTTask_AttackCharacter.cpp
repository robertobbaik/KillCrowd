// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackCharacter.h"
#include "AIController.h"
#include "BaseCharacter.h"
#include "BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "Kismet/GameplayStatics.h"

UBTTask_AttackCharacter::UBTTask_AttackCharacter()
{
}

EBTNodeResult::Type UBTTask_AttackCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	
	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
	if (AActor* TargetPlayer = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Player"))))
	{
		if (ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(AIPawn))
		{
			EnemyCharacter->Attack();
		}
		
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
