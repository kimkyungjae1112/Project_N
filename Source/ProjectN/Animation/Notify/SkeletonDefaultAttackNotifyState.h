// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SkeletonDefaultAttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API USkeletonDefaultAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	USkeletonDefaultAttackNotifyState();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	void MakeLineTrace(AActor* Target);

	UPROPERTY()
	TSet<AActor*> HitTarget;
};
