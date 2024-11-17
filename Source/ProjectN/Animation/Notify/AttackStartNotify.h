// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackStartNotify.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UAttackStartNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAttackStartNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
