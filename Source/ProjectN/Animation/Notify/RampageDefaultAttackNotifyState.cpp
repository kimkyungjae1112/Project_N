// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/RampageDefaultAttackNotifyState.h"
#include "GameFramework/Character.h"

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
}

void URampageDefaultAttackNotifyState::MakeSphereTrace(ACharacter* Character)
{
	FVector LeftHandLoc = Character->GetMesh()->GetSocketLocation(TEXT("Hand_L"));
	FRotator LeftHandRot = Character->GetMesh()->GetSocketRotation(TEXT("Hand_L"));
	
	FVector RightHandLoc = Character->GetMesh()->GetSocketLocation(TEXT("Hand_R"));
	FRotator RightHandRot = Character->GetMesh()->GetSocketRotation(TEXT("Hand_R"));

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, true, Character);

	bool bLeftHandHit = Character->GetWorld()->SweepSingleByChannel(HitResult, LeftHandLoc, LeftHandLoc, LeftHandRot.Quaternion(), ECC_GameTraceChannel1, FCollisionShape::MakeBox(FVector(100.f)), Params);
	bool bRightHandHit = Character->GetWorld()->SweepSingleByChannel(HitResult, RightHandLoc, RightHandLoc, RightHandRot.Quaternion(), ECC_GameTraceChannel1, FCollisionShape::MakeBox(FVector(100.f)), Params);

	DrawDebugBox(Character->GetWorld(), LeftHandLoc, FVector(100.f), FColor::Red, false);
	DrawDebugBox(Character->GetWorld(), RightHandLoc, FVector(100.f), FColor::Red, false);

	if ((bLeftHandHit || bRightHandHit) && !HitTarget.Contains(HitResult.GetActor()))  
	{
		HitTarget.Add(HitResult.GetActor());

		UE_LOG(LogTemp, Display, TEXT("공격됨?"));
		DrawDebugSphere(Character->GetWorld(), HitResult.ImpactPoint, 16.f, 32, FColor::Green, false, 3.f);
	}

}
