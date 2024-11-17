// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PNBattleSystemComponent.generated.h"

UENUM()
enum class EAttackState : uint8
{
	ASIdle,
	ASLeft,
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
	void Charge();
	void Attack();
	void ChargeAttack();
	void LightAttack();
	void HeavyAttack();

	void SuccessCharge();
	void FailCharge();

private:
	UPROPERTY(VisibleAnywhere, Category = "Utility")
	TObjectPtr<class ACharacter> Player;

	UPROPERTY(VisibleAnywhere, Category = "Utility")
	TObjectPtr<class UAnimInstance> Anim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Utility", meta = (AllowPrivateAccess = "true"))
	EAttackState CurrentAttackState;

private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> AttackMontage;
};
