// Fill out your copyright notice in the Description page of Project Settings.


#include "AssassinCharacter.h"

#include "KillCrowdGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnitConversion.h"

AAssassinCharacter::AAssassinCharacter()
{
	WeaponMeshComp->SetupAttachment(GetMesh(), TEXT("hand_r"));
}

void AAssassinCharacter::SetDamage()
{
	float MinDistance = 300.0f;
	
	if (AKillCrowdGameMode* GameMode = AKillCrowdGameMode::GetInstance())
	{
		TSet<ABaseEnemyCharacter*> Enemies = GameMode->AliveEnemyPool;

		// 메쉬의 2D 평면에서의 전방 벡터 (Z축 제거)
		FVector CharacterForward = GetMesh()->GetForwardVector();
		CharacterForward.Z = 0.0f;
		CharacterForward.Normalize();
        
		FVector CharacterLocation = GetActorLocation();

		for (ABaseEnemyCharacter* Enemy : Enemies)
		{
			if (!Enemy || !Enemy->bIsAlive)
				continue;

			FVector EnemyLocation = Enemy->GetActorLocation();
			float Distance = FVector::Distance(CharacterLocation, EnemyLocation);
            
			if (Distance < MinDistance)
			{
				FVector DirectionToEnemy = EnemyLocation - CharacterLocation;
				DirectionToEnemy.Z = 0.0f; 
				DirectionToEnemy.Normalize();
				
				FVector CrossProduct = FVector::CrossProduct(CharacterForward, DirectionToEnemy);
				float DotProduct = FVector::DotProduct(CharacterForward, DirectionToEnemy);
				
				float AngleInRadians = FMath::Atan2(CrossProduct.Z, DotProduct);
				float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians);
				
				if (AngleInDegrees >= 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Enemy Hit! Distance: %.2f, Angle: %.2f"), Distance, AngleInDegrees);
					UGameplayStatics::ApplyDamage(Enemy, 50.0f, GetController(), this, UDamageType::StaticClass());
				}
			}
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
				PlayAnimMontage(MapAttackMontage[CurrentWeaponType], 3.0f);
				float Duration = MapAttackMontage[CurrentWeaponType]->GetPlayLength();

				//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetMesh()->GetForwardVector().ToString());
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetActorForwardVector().ToString());
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




