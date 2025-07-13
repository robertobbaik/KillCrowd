// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdatePlayerLocation.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = "Update Player Location";
	Interval = 0.1f;
	RandomDeviation = 0.0f;
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return;

	AActor* PlayerActor = Cast<AActor>(BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName));

	if (PlayerActor)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player Actor: %s"), *PlayerActor->GetName());
		FVector CurrentPlayerLocation = PlayerActor->GetActorLocation();
		BlackboardComp->SetValueAsVector(PlayerLocationKey.SelectedKeyName, CurrentPlayerLocation);
	}
}
