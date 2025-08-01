// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

#include "EnemyAIController.h"
#include "KillCrowdGameMode.h"
#include "ShaderCompiler.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
}

void ABaseEnemyCharacter::SetActive(bool bIsActive)
{
	SetActorHiddenInGame(!bIsActive);
	SetActorEnableCollision(bIsActive);
	SetActorTickEnabled(bIsActive);
	bIsAlive = bIsActive;

	if (bIsActive)
	{
		if (AIController)
		{
			AIController->ResetAIState();
		}
	}
	else
	{
		if (AIController)
		{
			AIController->GetBrainComponent()->StopLogic(TEXT("Pooled"));
		}

		USkeletalMeshComponent* MeshComp = GetMesh();
		if (!MeshComp) return;
    
		UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
		if (!AnimInstance) return;

		AnimInstance->StopAllMontages(0.0f);
		MeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		if (AKillCrowdGameMode* GameMode = AKillCrowdGameMode::GetInstance())
		{
			GameMode->ReturnEnemyPool(this);
		}
	}
}


void ABaseEnemyCharacter::Initialize(const FEnemyStats& EnemyStats)
{
	float Temp = 0.f;
	MaterialInstance->GetScalarParameterDefaultValue(TEXT("Disolve"), Temp);
	UE_LOG(LogTemp, Warning, TEXT("Temp : %f"), Temp);
	
	MaterialInstance->SetScalarParameterValue(TEXT("Disolve"), -1.f);
	
	MaxHealth = EnemyStats.MaxHealth;
	AttackDamage = EnemyStats.AttackDamage;
	MovementSpeed = EnemyStats.MovementSpeed;
	AttackRange = EnemyStats.AttackRange;
	AttackCoolDown = EnemyStats.AttackCoolDown;
	ExperienceValue = EnemyStats.ExperienceValue;

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	AIController->Initialize(EnemyStats);
}

void ABaseEnemyCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("BaseEnemy Death"));
	if (AKillCrowdGameMode* GameMode = AKillCrowdGameMode::GetInstance())
	{
		GameMode->RemoveAlivePool(this);
	}
	
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->StopAllMontages(0.0f);
		if (DeathAnim)
		{
			PlayAnimMontage(DeathAnim);
			UE_LOG(LogTemp, Warning, TEXT("Death"));
			OnEnemyDeath();
			float Duration = DeathAnim->GetPlayLength();
		
			FTimerHandle TimerHandle;
			GetWorldTimerManager().SetTimer(TimerHandle, [this]()
			{
				SetActive(false);
			}, Duration + 0.2f, false);
		}
	}
}

float ABaseEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                      class AController* EventInstigator, AActor* DamageCauser)
{
	if (!bIsAlive) return 0.0f;
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, this);

	UE_LOG(LogTemp, Warning, TEXT("Set Damage"));
	UE_LOG(LogTemp, Warning, TEXT("MAX Health : %f"), MaxHealth);
	MaxHealth -= ActualDamage;
	UE_LOG(LogTemp, Warning, TEXT("MAX Health : %f"), MaxHealth);
	if (MaxHealth <= 0.0f)
	{
		AIController->Death();
		bIsAlive = false;
	}
	
	return ActualDamage;
}

