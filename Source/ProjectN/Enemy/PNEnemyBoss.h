// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/PNEnemyBase.h"
#include "PNEnemyBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNEnemyBoss : public APNEnemyBase
{
	GENERATED_BODY()

public:
	APNEnemyBoss();

protected:
	virtual void BeginPlay() override;
	
public:
	/* AI Interface */
	virtual float GetMeleeAttackInRange() override;
	virtual void Attack_1() override;
	virtual void Attack_2() override;

	virtual class APNAIControllerBase* GetAIController();

	/* EnemyApplyDamage Interface */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;

	virtual void SetDead() override;

private:
	void BeginAttack_1_Default();
	void EndAttack_1_Default(class UAnimMontage* Target, bool IsProperlyEnded);


/* 유틸 */
private:
	class APNAIControllerBoss* GetMyController();

/* 몽타주 섹션 */
private:
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TObjectPtr<class UAnimInstance> Anim;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> Attack_1_Montage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> Attack_2_Montage;

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class USkeletalMeshComponent> SwordMeshComp;

};
