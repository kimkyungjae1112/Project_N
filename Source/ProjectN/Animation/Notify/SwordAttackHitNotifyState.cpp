// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/SwordAttackHitNotifyState.h"
#include "Interface/EnemyApplyDamageInterface.h"
#include "Interface/WeaponSocketCarryInterface.h"

USwordAttackHitNotifyState::USwordAttackHitNotifyState()
{
	Damage = 0.f;
	DamageType = TEXT("");
}

void USwordAttackHitNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (UPNBattleSystemComponent* BSComp = MeshComp->GetOwner()->GetComponentByClass<UPNBattleSystemComponent>())
	{
		DecideAttackType(BSComp->GetAttackState());
	}
}

void USwordAttackHitNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	MakeLineTrace(MeshComp->GetOwner());
}

void USwordAttackHitNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	HitEnemys.Empty();
}

void USwordAttackHitNotifyState::DecideAttackType(EAttackState AttackState)
{
	switch (AttackState)
	{
	case EAttackState::ASLight:
		Damage = 300.f;
		DamageType = TEXT("Light");
		break;
	case EAttackState::ASHeavy:
		Damage = 500.f;
		DamageType = TEXT("Heavy");
		break;
	case EAttackState::ASDash:
		Damage = 500.f;
		DamageType = TEXT("Dash");
		break;
	case EAttackState::ASCharge:
		Damage = 600.f;
		DamageType = TEXT("Charge");
		break;
	default:
		Damage = -1.f;
		DamageType = TEXT("Error");
		UE_LOG(LogTemp, Error, TEXT("Player Sword Hit Error"));
		break;
	}
}

void USwordAttackHitNotifyState::MakeLineTrace(AActor* Owner)
{
	IWeaponSocketCarryInterface* WeaponInterface = Cast<IWeaponSocketCarryInterface>(Owner);
	if (WeaponInterface)
	{
		USkeletalMeshComponent* SwordMesh = WeaponInterface->GetWeaponMeshComponent();
		if (SwordMesh)
		{
			FVector StartLoc = SwordMesh->GetSocketLocation(TEXT("SwordBoneStart"));
			FVector EndLoc = SwordMesh->GetSocketLocation(TEXT("SwordBoneEnd"));

			FHitResult HitResult;
			FCollisionQueryParams Params(NAME_None, true, Owner);
			//DrawDebugLine(Owner->GetWorld(), StartLoc, EndLoc, FColor::Red, false, 2.f);

			bool bHit = Owner->GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_GameTraceChannel2, Params);
			if (bHit && !HitEnemys.Contains(HitResult.GetActor()))
			{
				DrawDebugSphere(Owner->GetWorld(), HitResult.ImpactPoint, 12.f, 32, FColor::Green, false, 3.f);
				HitEnemys.Add(HitResult.GetActor());

				if (IEnemyApplyDamageInterface* Enemy = Cast<IEnemyApplyDamageInterface>(HitResult.GetActor()))
				{
					Enemy->ApplyDamage(Damage, Owner, DamageType, HitResult.ImpactPoint);
				}
			}
		}
	}
}


