// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PNBattleSystemComponent.generated.h"

UENUM()
enum class EAttackState : uint8
{
	ASIdle,
	ASLight,
	ASHeavy,
	ASCharge
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


	/* Heavy Attack */
	void BeginHeavyAttack();
	void EndHeavyAttack(class UAnimMontage* Target, bool IsProperlyEnded);
	void SetTimerHeavyAttack();
	void CheckTimerHeavyAttack();

	int32 CurrentHeavyAttackCombo = 0;
	bool HasNextHeavyAttack = false;
	FTimerHandle HeavyAttackTimer;


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
};
