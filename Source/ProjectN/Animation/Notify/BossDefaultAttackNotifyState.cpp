// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/BossDefaultAttackNotifyState.h"
#include "Engine/OverlapResult.h"
#include "Engine/DamageEvents.h"
#include "Interface/AIInterface.h"
#include "Interface/WeaponSocketCarryInterface.h"
#include "AI/Controller/PNAIControllerBase.h"

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

	if (MeshComp->GetOwner())
	{
		MakeLineTrace(MeshComp->GetOwner());
	}
}

void UBossDefaultAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	Hits.Empty();

	IAIInterface* Interface = Cast<IAIInterface>(MeshComp->GetOwner());
	IWeaponSocketCarryInterface* WeaponInterface = Cast<IWeaponSocketCarryInterface>(MeshComp->GetOwner());
	if (Interface && WeaponInterface)
	{
		if (CanComboAttack(MeshComp->GetOwner()) && WeaponInterface->GetCurrentCombo() != 3)
		{
			Interface->NextComboAttack();
		}
	}
}

void UBossDefaultAttackNotifyState::MakeLineTrace(AActor* Owner)
{
	IWeaponSocketCarryInterface* WeaponInterface = Cast<IWeaponSocketCarryInterface>(Owner);
	if (WeaponInterface)
	{
		USkeletalMeshComponent* WeaponComp = WeaponInterface->GetWeaponMeshComponent();

		if (WeaponComp)
		{
			FVector StartBone = WeaponComp->GetSocketLocation(TEXT("SwordStartBone"));
			FVector EndBone = WeaponComp->GetSocketLocation(TEXT("SwordEndBone"));

			FHitResult HitResult;
			FCollisionQueryParams Params(NAME_None, true, Owner);
			DrawDebugLine(Owner->GetWorld(), StartBone, EndBone, FColor::Red, false, 2.f);


			bool bHit = Owner->GetWorld()->LineTraceSingleByChannel(HitResult, StartBone, EndBone, ECC_GameTraceChannel1, Params);
			if (bHit && !Hits.Contains(HitResult.GetActor()))
			{
				Hits.Add(HitResult.GetActor());
				
				IAIInterface* Interface = Cast<IAIInterface>(Owner);
				if (Interface)
				{
					FDamageEvent DamageEvent;
					HitResult.GetActor()->TakeDamage(500.f, DamageEvent, Interface->GetAIController(), Owner);
				}
			}
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
