// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "CharacterController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "KillCrowdGameMode.h"
#include "BaseEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));

	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel1);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);  
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); 
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ChangeWeapon(EWeaponType::Basic);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::Attack, 1.f, true);

	AttackSpeed = 1.f;
	MoveSpeed = 200.f;
	AttackRadius = 200.f;
	AttackAngle = 180.f;
	AttackDamage = 100.f;

	if (UCharacterMovementComponent* MovementComp = GetCharacterMovement())
	{
		MovementComp->MaxWalkSpeed = MoveSpeed;
	}
}
// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if (bIsAttack)
	// {
	// 	FRotator CurrentRotation = GetMesh()->GetRelativeRotation();
	// 	
	// 	FVector Direction = GetClosestEnemy() ? GetActorLocation() - GetClosestEnemy()->GetActorLocation() : GetActorLocation();
	// 	
	// 	FRotator TargetRotation = FRotator(0.f,Direction.Rotation().Yaw + 90, 0.f);
	// 	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f); // 10.f는 회전 속도
	// 	GetMesh()->SetRelativeRotation(NewRotation);
	// }
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ACharacterController* PlayerController = Cast<ACharacterController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ABaseCharacter::Move
					);
			}
		}
	}
}

void ABaseCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	const FVector2D MoveInput = Value.Get<FVector2D>();
	
	const float Length = MoveInput.GetSafeNormal().Length();
	
	if (!FMath::IsNearlyZero(Length))
	{
		FVector Direction = FVector(MoveInput.X, MoveInput.Y, 0);
		FRotator CurrentRotation = GetMesh()->GetRelativeRotation();
		
		FRotator TargetRotation = FRotator(0.f,Direction.Rotation().Yaw - 90, 0.f);
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f); 
		GetMesh()->SetRelativeRotation(NewRotation);
		// if (!bIsAttack)
		// {
		// 	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 10.f); 
		// 	GetMesh()->SetRelativeRotation(NewRotation);
		// }
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetMesh()->GetForwardVector().ToString());
		AddMovementInput(Direction, Length);
	}
}

ABaseEnemyCharacter* ABaseCharacter::GetClosestEnemy()
{
	if (AKillCrowdGameMode* GameMode = AKillCrowdGameMode::GetInstance())
	{
		float MinDistance = AttackRadius;
		TSet<ABaseEnemyCharacter*> Enemies = GameMode->AliveEnemyPool;
		ABaseEnemyCharacter* NearestEnemy = nullptr;
	
		for (ABaseEnemyCharacter* Enemy : Enemies)
		{
			float Distance = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				NearestEnemy = Enemy;
			}
		}

		return NearestEnemy;
	}
	
	return nullptr;
}




