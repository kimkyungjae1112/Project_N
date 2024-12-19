// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/PNEnemyBase.h"
#include "Interface/WeaponSocketCarryInterface.h"
#include "Interface/BossAttackHitInterface.h"
#include "PNEnemyBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNEnemyBoss : public APNEnemyBase, public IWeaponSocketCarryInterface, public IBossAttackHitInterface
{
	GENERATED_BODY()

public:
	APNEnemyBoss();

	UFUNCTION(BlueprintCallable)
	void TestStart();

protected:
	virtual void BeginPlay() override;
	
public:
	/* AI Interface */
	virtual float GetMeleeAttackInRange() override;
	virtual void Attack_1() override;
	virtual void Attack_2() override;
	virtual void Attack_3() override;
	virtual void Attack_4() override;
	virtual void Attack_5() override;
	virtual void Attack_6() override;

	virtual class APNAIControllerBase* GetAIController() override;
	virtual void NextComboAttack() override;

	/* EnemyApplyDamage Interface */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;

	virtual void SetDead() override;

	/* Weapon Socket Carry */
	virtual class USkeletalMeshComponent* GetWeaponMeshComponent() override;
	virtual uint8 GetCurrentCombo() override;

	/* UI */
	void DisplayStatus();

	/* Start Motion */
	void StartMotion();

/* 공격 */
private:
	void BeginMeleeAttack_1();
	void EndMeleeAttack_1(class UAnimMontage* Target, bool IsProperlyEnded);

	void BeginMeleeAttack_2();
	void EndMeleeAttack_2(class UAnimMontage* Target, bool IsProperlyEnded);

	void BeginMeleeAttack_3();
	void EndMeleeAttack_3(class UAnimMontage* Target, bool IsProperlyEnded);
	void Attack_3_MotionWarpSet();
	virtual void Attack_3_HitCheck() override;

	void BeginMeleeAttack_4();
	void EndMeleeAttack_4(class UAnimMontage* Target, bool IsProperlyEnded);
	void Attack_4_MotionWarpSet();
	virtual void Attack_4_HitCheck() override;

	void BeginRangedAttack_1();
	void EndRangedAttack_1(class UAnimMontage* Target, bool IsProperlyEnded);
	virtual void Attack_5_HitCheck() override;

	void BeginRangedAttack_2();
	void EndRangedAttack_2(class UAnimMontage* Target, bool IsProperlyEnded);
	virtual void Attack_6_HitCheck() override;

/* 공격 관련 데이터 */
private:
	uint8 Attack_1_Combo = 0;

/* 시작 모션 */
private:
	void BeginStartMotion();
	void EndStartMotion(class UAnimMontage* Target, bool IsProperlyEnded);



/* 유틸 */
private:
	class APNAIControllerBoss* GetMyController();

/* 몽타주 섹션 */
private:
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	TObjectPtr<class UAnimInstance> Anim;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> MeleeAttack_1_Montage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> MeleeAttack_2_Montage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> MeleeAttack_3_Montage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> MeleeAttack_4_Montage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> RangedAttack_1_Montage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> RangedAttack_2_Montage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> StartMotionMontage;

/* 컴포넌트 */
private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class USkeletalMeshComponent> SwordMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "MotionWarp")
	TObjectPtr<class UMotionWarpingComponent> MotionWarpComp;

/* UI */
private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBossStatusWidget> BossStatusClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UBossStatusWidget> BossStatusPtr;

};
