// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PNCharacterBase.h"
#include "Interface/AIInterface.h"
#include "PNEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNEnemyBase : public APNCharacterBase, public IAIInterface
{
	GENERATED_BODY()

public:
	virtual float GetMeleeAttackInRange() override;
	virtual void Attack_1() override;
	virtual void Attack_2() override;

	virtual void SetAttack_1_Delegate(const FOnAttack_1_Finished& InOnAttack_1_Finished);
	virtual void SetAttack_2_Delegate(const FOnAttack_2_Finished& InOnAttack_2_Finished);

	virtual class APNAIControllerBase* GetAIController() override;

protected:
	FOnAttack_1_Finished OnAttack_1_Finished;
	FOnAttack_2_Finished OnAttack_2_Finished;
};
