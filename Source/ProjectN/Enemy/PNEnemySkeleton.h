// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/PNEnemyCommonBase.h"
#include "Interface/WeaponSocketCarryInterface.h"
#include "PNEnemySkeleton.generated.h"

UENUM()
enum class EWeaponType : uint8
{
	Sword = 0,
	Axe,
	Spear
};

UCLASS()
class PROJECTN_API APNEnemySkeleton : public APNEnemyCommonBase, public IWeaponSocketCarryInterface
{
	GENERATED_BODY()
	
public:
	APNEnemySkeleton();

	/* AI Interface */
	virtual float GetMeleeAttackInRange() override;
	virtual void Attack_1() override;
	virtual void Attack_2() override;

	virtual class APNAIControllerBase* GetAIController() override;

	virtual void NextComboAttack() override;

	/* EnemyApplyDamage Interface */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;

	virtual void SetDead() override;

	/* Weapon Socket Interface */
	virtual USkeletalMeshComponent* GetWeaponMeshComponent() override;

protected:
	virtual void BeginPlay() override;


/* 메쉬 */
private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class USkeletalMeshComponent> WeaponMeshComp;


/* 유틸리티 */
private:
	class APNAIControllerSkeleton* GetMyController();

	UPROPERTY(VisibleAnywhere, Category = "Util")
	TObjectPtr<class UAnimInstance> Anim;

	UPROPERTY(EditAnywhere, Category = "WeaponType")
	EWeaponType WeaponType;

/* 공격 */
private:
	void BeginDefaultAttack();
	void EndDefaultAttack(class UAnimMontage* Target, bool IsProperlyEnded);

/* 피격 */
private:
	void BeginHurt(const FName& DamageType, const FVector& ImpactLocation);
	void EndHurt(class UAnimMontage* Target, bool IsProperlyEnded);

/* 공격 관련 데이터 */
private:
	uint8 DefaultAttackCombo;

/* 몽타주 */
private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TArray<class UAnimMontage*> SwordMontages;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TArray<class UAnimMontage*> AxeMontages;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TArray<class UAnimMontage*> SpearMontages;

	UPROPERTY(VisibleAnywhere, Category = "Montage")
	TArray<class UAnimMontage*> CurrentWeaponMontages;

/* 이펙트 */
private:
	UPROPERTY(EditAnywhere, Category = "Effect")
	TObjectPtr<class UNiagaraSystem> DefaultImpactNiagara;

};
