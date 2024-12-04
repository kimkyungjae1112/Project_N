// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "RampageDefaultAttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API URampageDefaultAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	URampageDefaultAttackNotifyState();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

private:
	void MakeSphereTrace(class ACharacter* Character);
	bool CanComboAttack(AActor* Owner);

	UPROPERTY()
	TSet<AActor*> HitTarget;
};
