// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"

#include "KillCrowdGameMode.h"
#include "Kismet/GameplayStatics.h"

AAssassinCharacter::AAssassinCharacter()
{
	WeaponMeshComp->SetupAttachment(GetMesh(), TEXT("hand_r"));
}

void AAssassinCharacter::SetDamage()
{	float MinDistance = 300.0f;

	TSet<ABaseEnemyCharacter*> Enemies = GameMode->AliveEnemyPool;
	
	for (ABaseEnemyCharacter* Enemy : Enemies)
	{
		float Distance = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
		if (Distance < MinDistance && Enemy->bIsAlive)
		{
			UGameplayStatics::ApplyDamage(Enemy, 50.0f, GetController(), this,	UDamageType::StaticClass());	
		}
	}
}

void AAssassinCharacter::Attack()
{
	float MinDistance = 150.0f;
	
	if (ABaseEnemyCharacter* NearestEnemy = GetClosestEnemy())
	{
		if (FVector::Distance(GetActorLocation(), NearestEnemy->GetActorLocation()) < MinDistance)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack"));

			if (MapAttackMontage[CurrentWeaponType])
			{
				PlayAnimMontage(MapAttackMontage[CurrentWeaponType]);
				float Duration = MapAttackMontage[CurrentWeaponType]->GetPlayLength();

				bIsAttack = true;
				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, [this]()
				{
					bIsAttack = false;
				},Duration, false);
			}
		}
	}
	

}

void AAssassinCharacter::ChangeWeapon(const EWeaponType WeaponType)
{
	UE_LOG(LogTemp, Warning, TEXT("Change Weapon"));
	switch (WeaponType)
	{
	case EWeaponType::Basic:
		break;
	case EWeaponType::Advanced_First:
		break;
	case EWeaponType::Advanced_Second:
		break;
	}
}




