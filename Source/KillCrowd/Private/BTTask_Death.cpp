// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Death.h"

#include "AIController.h"
#include "BaseEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_String.h"

UBTTask_Death::UBTTask_Death()
{
	NodeName = "BTTask_Death";
}

EBTNodeResult::Type UBTTask_Death::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	
	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	if (ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(AIPawn))
	{
		EnemyCharacter->Death();
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
