// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AKillCrowdGameMode;
class ABaseEnemyCharacter;
struct FInputActionValue;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Basic = 0 UMETA(DisplayName = "Basic"),
	Advanced_First = 1 UMETA(DisplayName = "Advanced First"),
	Advanced_Second = 2 UMETA(DisplayName = "Advanced Second"),
};

UCLASS(Abstract, NotBlueprintable)
class KILLCROWD_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	bool bIsAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess))
	EWeaponType CurrentWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	UStaticMeshComponent* WeaponMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TMap<EWeaponType, UAnimMontage*> MapAttackMontage;
	
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	ABaseEnemyCharacter* GetClosestEnemy();

	virtual void ChangeWeapon(const EWeaponType WeaponType) PURE_VIRTUAL(ABaseCharacter::ChangeWeapon, )
	virtual void Attack() PURE_VIRTUAL(ABaseCharacter::Attack,)
	
public:
	virtual void SetDamage() PURE_VIRTUAL(ABaseCharacter::Attack,)
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

private:
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackDamage;
};	
