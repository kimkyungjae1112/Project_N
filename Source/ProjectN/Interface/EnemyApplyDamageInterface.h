// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyApplyDamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyApplyDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTN_API IEnemyApplyDamageInterface
{
	GENERATED_BODY()

public:
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) = 0;
};
