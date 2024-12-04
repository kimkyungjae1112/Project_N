// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/RampageDefaultAttackNotifyState.h"
#include "GameFramework/Character.h"
#include "Engine/OverlapResult.h"
#include "Interface/AIInterface.h"

URampageDefaultAttackNotifyState::URampageDefaultAttackNotifyState()
{
}

void URampageDefaultAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

}

void URampageDefaultAttackNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character)
	{
		MakeSphereTrace(Character);
	}
}

void URampageDefaultAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	HitTarget.Empty();
	if (CanComboAttack(MeshComp->GetOwner()))
	{
		IAIInterface* Interface = Cast<IAIInterface>(MeshComp->GetOwner());
		if (Interface)
		{
			Interface->NextComboAttack();
		}
	}
}

void URampageDefaultAttackNotifyState::MakeSphereTrace(ACharacter* Character)
{
	FVector LeftHandLoc = Character->GetMesh()->GetSocketLocation(TEXT("Hand_L"));
	FRotator LeftHandRot = Character->GetMesh()->GetSocketRotation(TEXT("Hand_L"));
	
	FVector RightHandLoc = Character->GetMesh()->GetSocketLocation(TEXT("Hand_R"));
	FRotator RightHandRot = Character->GetMesh()->GetSocketRotation(TEXT("Hand_R"));

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, true, Character);
	float BoxExtent = 25.f;

	bool bLeftHandHit = Character->GetWorld()->SweepSingleByChannel(HitResult, LeftHandLoc, LeftHandLoc, LeftHandRot.Quaternion(), ECC_GameTraceChannel1, FCollisionShape::MakeBox(FVector(BoxExtent)), Params);
	bool bRightHandHit = Character->GetWorld()->SweepSingleByChannel(HitResult, RightHandLoc, RightHandLoc, RightHandRot.Quaternion(), ECC_GameTraceChannel1, FCollisionShape::MakeBox(FVector(BoxExtent)), Params);

	DrawDebugBox(Character->GetWorld(), LeftHandLoc, FVector(), FColor::Red, false);
	DrawDebugBox(Character->GetWorld(), RightHandLoc, FVector(), FColor::Red, false);

	if ((bLeftHandHit || bRightHandHit) && !HitTarget.Contains(HitResult.GetActor()))  
	{
		HitTarget.Add(HitResult.GetActor());

		DrawDebugSphere(Character->GetWorld(), HitResult.ImpactPoint, 16.f, 32, FColor::Green, false, 3.f);
	}
}

bool URampageDefaultAttackNotifyState::CanComboAttack(AActor* Owner)
{
	FVector Origin = Owner->GetActorLocation();
	float Radius = 300.f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Params(NAME_None, true, Owner);

	return Owner->GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Radius), Params);
}
