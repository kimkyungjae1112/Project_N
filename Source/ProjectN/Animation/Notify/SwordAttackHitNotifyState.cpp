// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/SwordAttackHitNotifyState.h"
#include "Character/PNCharacter.h"
#include "Interface/EnemyApplyDamageInterface.h"

void USwordAttackHitNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void USwordAttackHitNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	APNCharacter* Character = Cast<APNCharacter>(MeshComp->GetOwner());
	if (Character)
	{
		MakeLineTrace(Character);
	}
}

void USwordAttackHitNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	HitEnemys.Empty();
}

void USwordAttackHitNotifyState::MakeLineTrace(APNCharacter* Character)
{
	USkeletalMeshComponent* SwordMesh = Character->GetWeapon();
	if (SwordMesh && SwordMesh->DoesSocketExist(FName("SwordBoneStart")) && SwordMesh->DoesSocketExist(FName("SwordBoneEnd")))
	{
		FVector StartLoc = SwordMesh->GetSocketLocation(TEXT("SwordBoneStart"));
		FVector EndLoc = SwordMesh->GetSocketLocation(TEXT("SwordBoneEnd"));

		FHitResult HitResult;
		FCollisionQueryParams Params(NAME_None, true, Character);
		DrawDebugLine(Character->GetWorld(), StartLoc, EndLoc, FColor::Red, false, 2.f);

		bool bHit = Character->GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_GameTraceChannel2, Params);
		if (bHit && !HitEnemys.Contains(HitResult.GetActor()))
		{
			DrawDebugSphere(Character->GetWorld(), HitResult.ImpactPoint, 12.f, 32, FColor::Green, false, 3.f);
			HitEnemys.Add(HitResult.GetActor());
		
			if (IEnemyApplyDamageInterface* Enemy = Cast<IEnemyApplyDamageInterface>(HitResult.GetActor()))
			{
				Enemy->ApplyDamage(500.f, Character, TEXT("Default"), HitResult.ImpactPoint);
			}
		}
	}
}


