// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/BossAttack_5_HitNotify.h"
#include "Interface/BossAttackHitInterface.h"

void UBossAttack_5_HitNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (IBossAttackHitInterface* Interface = Cast<IBossAttackHitInterface>(MeshComp->GetOwner()))
	{
		Interface->Attack_5_HitCheck();
	}
}
