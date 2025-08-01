// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KILLCROWD_API UBTTask_FindPlayerCharacter : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_FindPlayerCharacter();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
