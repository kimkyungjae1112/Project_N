
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
	virtual float GetDetectRadius() override;

	virtual void Attack_1() override;
	virtual void Attack_2() override;
	virtual void Attack_3() override;
	virtual void Attack_4() override;
	virtual void Attack_5() override;
	virtual void Attack_6() override;

	virtual void SetAttack_1_Delegate(const FOnAttack_1_Finished& InOnAttack_1_Finished) override;
	virtual void SetAttack_2_Delegate(const FOnAttack_2_Finished& InOnAttack_2_Finished) override;
	virtual void SetAttack_3_Delegate(const FOnAttack_3_Finished& InOnAttack_3_Finished) override;
	virtual void SetAttack_4_Delegate(const FOnAttack_4_Finished& InOnAttack_4_Finished) override;
	virtual void SetAttack_5_Delegate(const FOnAttack_5_Finished& InOnAttack_5_Finished) override;
	virtual void SetAttack_6_Delegate(const FOnAttack_6_Finished& InOnAttack_6_Finished) override;

	virtual class APNAIControllerBase* GetAIController() override;
	
	virtual void NextComboAttack() override;

	/* EnemyApplyDamage Interface */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;


	virtual void SetDead();

protected:
	FOnAttack_1_Finished OnAttack_1_Finished;
	FOnAttack_2_Finished OnAttack_2_Finished;
	FOnAttack_3_Finished OnAttack_3_Finished;
	FOnAttack_4_Finished OnAttack_4_Finished;
	FOnAttack_5_Finished OnAttack_5_Finished;
	FOnAttack_6_Finished OnAttack_6_Finished;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UPNEnemyStatComponent> StatComp;
};
