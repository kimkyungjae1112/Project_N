// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/PNEnemyCommonBase.h"
#include "PNEnemyRampage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNEnemyRampage : public APNEnemyCommonBase
{
	GENERATED_BODY()
	
public:
	APNEnemyRampage();

	/* AI Interface */
	virtual float GetMeleeAttackInRange() override;
	virtual void Attack_1() override;
	virtual void Attack_2() override;

	virtual class APNAIControllerBase* GetAIController() override;

	/* 대미지 전달 */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;

protected:
	virtual void BeginPlay() override;


/* 유틸리티 */
private:
	class APNAIControllerRampage* GetMyController();

	UPROPERTY(VisibleAnywhere, Category = "Util")
	TObjectPtr<class UAnimInstance> Anim;

/* 공격 */
private:
	void BeginDefaultAttack();
	void EndDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);

/* 공격 관련 데이터 */
private:
	float DefaultAttackRange;

/* 몽타주 */
private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DefaultAttackMontage;
};
