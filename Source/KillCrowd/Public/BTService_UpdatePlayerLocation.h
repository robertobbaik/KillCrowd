// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatePlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class KILLCROWD_API UBTService_UpdatePlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_UpdatePlayerLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackBoard")
	FBlackboardKeySelector PlayerKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackBoard")
	FBlackboardKeySelector PlayerLocationKey;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
