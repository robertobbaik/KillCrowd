// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AttackCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KILLCROWD_API UBTTask_AttackCharacter : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_AttackCharacter();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
