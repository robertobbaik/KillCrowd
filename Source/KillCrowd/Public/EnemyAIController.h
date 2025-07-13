// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Chasing = 0 UMETA(DisplayName = "Chasing"),
	Attacking = 1 UMETA(DisplayName = "Attacking"),
	Death = 2 UMETA(DisplayName = "Death")
};
UCLASS()
class KILLCROWD_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ABaseEnemyCharacter* EnemyCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBlackboardComponent* BlackboardComp;

	UFUNCTION(BlueprintCallable, Category = "AI")
	void StopChasing();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float ChaseRadius = 1000.0f;

	//UFUNCTION(BlueprintCallable, Category = "AI")
	UFUNCTION()
	void Death();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

	// UFUNCTION()
	// UBlackboardComponent* GetBlackboard() const;

private:
	bool bIsChasing = false;
	static const FName PlayerKey;
	static const FName AliveKey;
};
