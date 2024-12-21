// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AIInterface.generated.h"

DECLARE_DELEGATE(FOnAttack_1_Finished)
DECLARE_DELEGATE(FOnAttack_2_Finished)
DECLARE_DELEGATE(FOnAttack_3_Finished)
DECLARE_DELEGATE(FOnAttack_4_Finished)
DECLARE_DELEGATE(FOnAttack_5_Finished)
DECLARE_DELEGATE(FOnAttack_6_Finished)

UINTERFACE(MinimalAPI)
class UAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTN_API IAIInterface
{
	GENERATED_BODY()

public:
	virtual float GetMeleeAttackInRange() = 0;
	virtual float GetDetectRadius() = 0;

	virtual void Attack_1() = 0;
	virtual void Attack_2() = 0;
	virtual void Attack_3() {};
	virtual void Attack_4() {};
	virtual void Attack_5() {};
	virtual void Attack_6() {};

	virtual void SetAttack_1_Delegate(const FOnAttack_1_Finished& InOnAttack_1_Finished) = 0;
	virtual void SetAttack_2_Delegate(const FOnAttack_2_Finished& InOnAttack_2_Finished) = 0;
	virtual void SetAttack_3_Delegate(const FOnAttack_3_Finished& InOnAttack_3_Finished) {};
	virtual void SetAttack_4_Delegate(const FOnAttack_4_Finished& InOnAttack_4_Finished) {};
	virtual void SetAttack_5_Delegate(const FOnAttack_4_Finished& InOnAttack_4_Finished) {};
	virtual void SetAttack_6_Delegate(const FOnAttack_4_Finished& InOnAttack_4_Finished) {};

	virtual class APNAIControllerBase* GetAIController() = 0;

	virtual void NextComboAttack() = 0;

	virtual void FirstDetectPlayer() = 0;
};
