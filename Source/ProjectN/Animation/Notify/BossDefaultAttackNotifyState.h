// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "BossDefaultAttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UBossDefaultAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UBossDefaultAttackNotifyState();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

private:
	void MakeLineTrace(AActor* Owner);
	bool CanComboAttack(AActor* Owner);

	TSet<AActor*> Hits;
};
