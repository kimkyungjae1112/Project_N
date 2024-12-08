// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/PNEnemyBase.h"
#include "Interface/EnemyCommonHpBarInterface.h"
#include "PNEnemyCommonBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNEnemyCommonBase : public APNEnemyBase, public IEnemyCommonHpBarInterface
{
	GENERATED_BODY()

public:
	APNEnemyCommonBase();

	virtual void NextComboAttack() override;

	/* EnemyApplyDamage Interface */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;

	/* EnemyCommonHpBar Interface */
	virtual void SetHpBar(class UEnemyHpBarWidget* InHpBar) override;

	virtual void SetDead() override { }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Effect")
	TObjectPtr<class UNiagaraComponent> ImpactNiagaraComop;

private:
	void DisplayDamageTextUI(float Damage);

private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UEnemyRefWidgetComponent> HpBarWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UEnemyRefWidgetComponent> DamageTextWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<class UEnemyRefWidget> HpBarClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> DamagedTextClass;
};
