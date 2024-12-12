// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BossAttackHitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBossAttackHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTN_API IBossAttackHitInterface
{
	GENERATED_BODY()

public:
	virtual void Attack_3_HitCheck() = 0;
	virtual void Attack_4_HitCheck() = 0;
	virtual void Attack_5_HitCheck() = 0;
	virtual void Attack_6_HitCheck() = 0;

};
