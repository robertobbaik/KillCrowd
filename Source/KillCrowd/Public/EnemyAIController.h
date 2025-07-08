// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class KILLCROWD_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ABaseEnemyCharacter* EnemyCharacter;
	
	UPROPERTY(EditAnywhere, Category="AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	AActor* TargetActor;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void StartChasing();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void StopChasing();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float ChaseRadius = 1000.0f;

	//UFUNCTION(BlueprintCallable, Category = "AI")
	UFUNCTION()
	void Death();

	UFUNCTION()
	void Operation();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	virtual void OnPossess(APawn* InPawn) override;

	

private:
	bool bIsChasing = false;
};
