// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/SkeletonDefaultAttackNotifyState.h"
#include "Interface/WeaponSocketCarryInterface.h"

USkeletonDefaultAttackNotifyState::USkeletonDefaultAttackNotifyState()
{
}

void USkeletonDefaultAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

}

void USkeletonDefaultAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	MakeLineTrace(MeshComp->GetOwner());
}

void USkeletonDefaultAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	HitTarget.Empty();
}

void USkeletonDefaultAttackNotifyState::MakeLineTrace(AActor* Target)
{
	IWeaponSocketCarryInterface* Interface = Cast<IWeaponSocketCarryInterface>(Target);
	if (Interface)
	{
		USkeletalMeshComponent* WeaponComp = Interface->GetWeaponMeshComponent();
		if (WeaponComp)
		{
			FVector StartLoc = WeaponComp->GetSocketLocation(TEXT("SwordBoneStart"));
			FVector EndLoc = WeaponComp->GetSocketLocation(TEXT("SwordBoneEnd"));

			FHitResult HitResult;
			FCollisionQueryParams Params(NAME_None, true, Target);
			DrawDebugLine(Target->GetWorld(), StartLoc, EndLoc, FColor::Red, false, 2.f);

			bool bHit = Target->GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_GameTraceChannel1, Params);
			if (bHit && !HitTarget.Contains(HitResult.GetActor()))
			{
				HitTarget.Add(HitResult.GetActor());

				DrawDebugSphere(Target->GetWorld(), HitResult.ImpactPoint, 12.f, 32, FColor::Green, false, 3.f);
			}
		}
	}
}
