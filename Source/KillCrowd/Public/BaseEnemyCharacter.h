// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Engine/DataTable.h"
#include "BaseEnemyCharacter.generated.h"

class AEnemyAIController;

USTRUCT(BlueprintType)
struct KILLCROWD_API FEnemyStats : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	float AttackCoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 ExperienceValue;
	
	FEnemyStats()
	{
		MaxHealth = 100.0f;
		AttackDamage = 20.0f;
		MovementSpeed = 300.0f;
		AttackRange = 150.0f;
		AttackCoolDown = 2.0f;
		ExperienceValue = 10;
	}
};

UCLASS(Abstract, NotBlueprintable)
class KILLCROWD_API ABaseEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyCharacter();
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInstanceDynamic* MaterialInstance;

	UFUNCTION(BlueprintCallable, Category="Status")
	void SetActive(bool bIsActive);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Status")
	bool bIsAlive;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DeathAnim;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackDamage;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackRange;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackCoolDown;

	UPROPERTY(EditAnywhere, Category = "Status")
	int ExperienceValue;

	UPROPERTY()
	AEnemyAIController* AIController;


public:
	virtual void Initialize(const FEnemyStats& EnemyStats) PURE_VIRTUAL(ABaseEnemyCharacter::Initialize, );
	virtual void Attack() PURE_VIRTUAL(ABaseEnemyCharacter::Attack, );
	virtual void Death();
	virtual void Operation() PURE_VIRTUAL(ABaseEnemyCharacter::Operation, );
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:

	
};
