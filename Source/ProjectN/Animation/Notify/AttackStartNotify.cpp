// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AttackStartNotify.h"
#include "Component/PNBattleSystemComponent.h"
#include "Character/PNCharacter.h"

UAttackStartNotify::UAttackStartNotify()
{
}

void UAttackStartNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	APNCharacter* Player = Cast<APNCharacter>(MeshComp->GetOwner());
	if (Player)
	{
		if (Player->GetIsCharge())
		{
			UPNBattleSystemComponent* BSComp = Cast<UPNBattleSystemComponent>(Player->GetComponentByClass<UPNBattleSystemComponent>());
			BSComp->SuccessCharge();
		}
		else
		{
			UPNBattleSystemComponent* BSComp = Cast<UPNBattleSystemComponent>(Player->GetComponentByClass<UPNBattleSystemComponent>());
			BSComp->FailCharge();
		}
	}
}
