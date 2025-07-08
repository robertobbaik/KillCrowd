// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AssassinCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class KILLCROWD_API AAssassinCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AAssassinCharacter();

	virtual void SetDamage() override;

protected:
	virtual void Attack() override;
	virtual void ChangeWeapon(const EWeaponType WeaponType) override;
};
