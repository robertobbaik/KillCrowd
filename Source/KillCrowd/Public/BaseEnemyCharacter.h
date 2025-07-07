// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BaseEnemyCharacter.generated.h"

class AEnemyAIController;

USTRUCT(BlueprintType)
struct KILLCROWD_API FEnemyStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Status")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackDamage;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackRange;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackCoolDown;

	UPROPERTY(EditAnywhere, Category = "Status")
	float DetectionRange;

	UPROPERTY(EditAnywhere, Category = "Status")
	int ExperienceValue;
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Status")
	void SetActive(bool bIsActive);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* DeathAnim;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Status")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackDamage;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackRange;

	UPROPERTY(EditAnywhere, Category = "Status")
	float AttackCoolDown;

	UPROPERTY(EditAnywhere, Category = "Status")
	float DetectionRange;

	UPROPERTY(EditAnywhere, Category = "Status")
	int ExperienceValue;

	UPROPERTY()
	AEnemyAIController* AIController;
	
public:
	virtual void Initialize(const FEnemyStats& EnemyStats) PURE_VIRTUAL(ABaseEnemyCharacter::Initialize, );
	virtual void Attack() PURE_VIRTUAL(ABaseEnemyCharacter::Attack, );
	virtual void Die() PURE_VIRTUAL(ABaseEnemyCharacter::Die, );
	virtual void Operation() PURE_VIRTUAL(ABaseEnemyCharacter::Operation, );
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:

	
};
