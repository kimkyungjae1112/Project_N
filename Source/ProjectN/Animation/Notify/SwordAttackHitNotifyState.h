// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Component/PNBattleSystemComponent.h"
#include "SwordAttackHitNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API USwordAttackHitNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	USwordAttackHitNotifyState();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	void DecideAttackType(EAttackState AttackState);
	void MakeLineTrace(AActor* Owner);

	UPROPERTY()
	TSet<AActor*> HitEnemys;
	
	float Damage;
	FName DamageType;

};
