// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/PNEnemyBase.h"
#include "PNEnemyTest.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNEnemyTest : public APNEnemyBase
{
	GENERATED_BODY()

public:
	APNEnemyTest();
	
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Effect")
	TObjectPtr<class UNiagaraComponent> NiagaraComp;
};
