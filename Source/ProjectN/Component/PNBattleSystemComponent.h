// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PNBattleSystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FInitBehaviorState)

UENUM()
enum class EAttackState : uint8
{
	ASIdle,
	ASLight,
	ASHeavy,
	ASCharge,
	ASDash
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTN_API UPNBattleSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPNBattleSystemComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FInitBehaviorState InitBehaviorState;

	FORCEINLINE EAttackState GetAttackState() { return CurrentAttackState; }

/* 공격 */
public:
	/* 좌클릭 눌렀을 때 실행되는 함수 */
	void Attack();
	/* 우클릭 눌렀을 때 실행되는 함수 */
	void HeavyAttack();

	/* 좌클릭 처음 눌렀을 때 계속 누르고 있는지 판별 */
	void SuccessCharge();
	void FailCharge();

	/* Light Attack */
	void LightAttack();

	/* Charge Attack */
	void ChargeAttack();

	/* Dash Attack */
	void BeginDashAttack();

	/* Assassination Attack */
	void BeginAssassinationAttack();

	/* Block */
	void BeginBlock();
	void EndBlock();
	
	/* Attacked */
	void BeginBlockAttacked();
	void BeginAttacked();

private:
	/* 차징 */
	void Charge();
	void EndCharge(class UAnimMontage* Target, bool IsProperlyEnded);

	/* Light Attack */
	void EndLightAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetTimerLightAttack();
	void CheckTimerLightAttack();

	int32 CurrentLightAttackCombo = 0;
	bool HasNextLightAttack = false;
	FTimerHandle LightAttackTimer;

	/* Charge Attack */
	void EndChargeAttack(class UAnimMontage* Target, bool IsProperlyEnded);

	/* Dash Attack */
	void EndDashAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	bool bIsDashAttacking = false;

	/* Assassination Attack */
	void DetectEnemyForAssassination();	//MakeSweepTrace 값에 따라 bCanAssassination 플래그 변경
	bool MakeSweepTrace();
	void AssassinationMotionWarpSet();
	bool bCanAssassination = false;
	FHitResult AssassinationedResult;

	/* Heavy Attack */
	void BeginHeavyAttack();
	void EndHeavyAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetTimerHeavyAttack();
	void CheckTimerHeavyAttack();

	int32 CurrentHeavyAttackCombo = 0;
	bool HasNextHeavyAttack = false;
	FTimerHandle HeavyAttackTimer;

	/* Attacked */
	void EndBlockAttacked(class UAnimMontage* Target, bool IsProperlyEnded);
	void EndAttacked(class UAnimMontage* Target, bool IsProperlyEnded);


/* UI */
private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UUserWidget> AssassinationUI;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> AssassinationUIClass;

/* Utility */
private:
	UPROPERTY(VisibleAnywhere, Category = "Utility")
	TObjectPtr<class ACharacter> Player;

	UPROPERTY(VisibleAnywhere, Category = "Utility")
	TObjectPtr<class UAnimInstance> Anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Utility", meta = (AllowPrivateAccess = "true"))
	EAttackState CurrentAttackState;

	UPROPERTY(VisibleAnywhere, Category = "Combo")
	TObjectPtr<class UPNCharacterComboDataAsset> ComboData;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UPNPlayerStatComponent> StatComp;

/* Montage */
private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> ChargeMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> ChargeAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> HeavyAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DashAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> AssassinationMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> BlockAttackedMontage;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> AttackedMontage;
};
