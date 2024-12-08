// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/BossDefaultAttackNotifyState.h"
#include "Engine/OverlapResult.h"
#include "Interface/AIInterface.h"

UBossDefaultAttackNotifyState::UBossDefaultAttackNotifyState()
{
}

void UBossDefaultAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

}

void UBossDefaultAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UBossDefaultAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	IAIInterface* Interface = Cast<IAIInterface>(MeshComp->GetOwner());
	if (Interface)
	{
		if (CanComboAttack(MeshComp->GetOwner()))
		{
			Interface->NextComboAttack();
		}
	}
}

bool UBossDefaultAttackNotifyState::CanComboAttack(AActor* Owner)
{
	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface)
	{
		float Radius = Interface->GetMeleeAttackInRange();

		TArray<FOverlapResult> OverlapResults;
		FVector Origin = Owner->GetActorLocation();
		FCollisionQueryParams Params(NAME_None, true, Owner);

		return Owner->GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Radius), Params);
	}

	return false;
}
