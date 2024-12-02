// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PNCharacterBase.h"
#include "Interface/AIInterface.h"
#include "Interface/EnemyApplyDamageInterface.h"
#include "Component/PNEnemyStatComponent.h"
#include "PNEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNEnemyBase : public APNCharacterBase, public IAIInterface, public IEnemyApplyDamageInterface
{
	GENERATED_BODY()

public:
	APNEnemyBase();

public:
	/* AI Interface */
	virtual float GetMeleeAttackInRange() override;
	virtual void Attack_1() override;
	virtual void Attack_2() override;

	virtual void SetAttack_1_Delegate(const FOnAttack_1_Finished& InOnAttack_1_Finished);
	virtual void SetAttack_2_Delegate(const FOnAttack_2_Finished& InOnAttack_2_Finished);

	virtual class APNAIControllerBase* GetAIController() override;
	

	/* 대미지 전달 */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;

protected:
	FOnAttack_1_Finished OnAttack_1_Finished;
	FOnAttack_2_Finished OnAttack_2_Finished;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UPNEnemyStatComponent> StatComp;
};
