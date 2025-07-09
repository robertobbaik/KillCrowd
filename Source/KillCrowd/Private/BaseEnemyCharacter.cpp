// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

#include "EnemyAIController.h"
#include "KillCrowdGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AEnemyAIController>(GetController());

	UMaterialInterface* CurrentMaterial = GetMesh()->GetMaterial(0);
	MaterialInstance = UMaterialInstanceDynamic::Create(CurrentMaterial, this);

	GetMesh()->SetMaterial(0, MaterialInstance);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel2);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap); 
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block); 
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	//AIController->StartChasing();

	IConsoleManager::Get().RegisterConsoleCommand(
		 TEXT("DeadEnemy"),
		 TEXT("Spawn a test enemy near player"),
		 FConsoleCommandDelegate::CreateLambda([this]()
		 {
			
		 }),
		 ECVF_Cheat
	 );
}

void ABaseEnemyCharacter::SetActive(bool bIsActive)
{
	SetActorHiddenInGame(!bIsActive);
	SetActorEnableCollision(bIsActive);
	SetActorTickEnabled(bIsActive);
	bIsAlive = bIsActive;

	if (bIsActive)
	{
		AIController->Operation();
	}
	else
	{
		AKillCrowdGameMode* GameMode = Cast<AKillCrowdGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->ReturnEnemyPool(this);
	}
}

void ABaseEnemyCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("BaseEnemy Death"));
	

}

float ABaseEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                      class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, this);
	
	UE_LOG(LogTemp, Warning, TEXT("Set Damage"));
	
	Death();
	return ActualDamage;
}



