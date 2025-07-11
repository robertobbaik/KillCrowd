// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BaseEnemyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"


const FName AEnemyAIController::PlayerKey = "Player";

AEnemyAIController::AEnemyAIController()
{
	
}

void AEnemyAIController::StartChasing()
{
	bIsChasing = true;

	if (TargetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("StartChasing"));
		SetFocus(TargetActor);
	
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(TargetActor);
		MoveRequest.SetAcceptanceRadius(50.f);
	
		FNavPathSharedPtr NavPath;
		FPathFollowingRequestResult Result = MoveTo(MoveRequest);
	}
}

void AEnemyAIController::StopChasing()
{
	bIsChasing = false;
	StopMovement();
}

void AEnemyAIController::Death()
{
	StopChasing();
	ClearFocus(EAIFocusPriority::Gameplay);
}

void AEnemyAIController::Operation()
{
	FTimerHandle TimerHandle;
	
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
	{
		//StartChasing();
	}, 0.2f, false);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result.IsSuccess())
	{
		if (EnemyCharacter)
		{
			//EnemyCharacter->Attack();
		}
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	EnemyCharacter = Cast<ABaseEnemyCharacter>(GetPawn());
	EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	if (BehaviorTree)
	{
		UBlackboardComponent* BlackboardComponent = BlackboardComp;
		if (UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent))
		{
			RunBehaviorTree(BehaviorTree);
		}
	}
	//TargetActor = Cast<AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ABaseCharacter::StaticClass()));

	//Operation();
}

UBlackboardComponent* AEnemyAIController::GetBlackboard() const
{
	return Blackboard;
}
