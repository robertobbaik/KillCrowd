// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_FindPlayerCharacter::UBTTask_FindPlayerCharacter()
{
}

EBTNodeResult::Type UBTTask_FindPlayerCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	
	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
	if (ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(	UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass())))
	{
		BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), PlayerCharacter);
		BlackboardComp->SetValueAsVector("Location", PlayerCharacter->GetActorLocation());
		AIController->SetFocus(PlayerCharacter);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
