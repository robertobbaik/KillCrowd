// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_KnifeAttack.h"

#include "BaseCharacter.h"

void UAnimNotify_KnifeAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		Character->SetDamage();
	}
}
