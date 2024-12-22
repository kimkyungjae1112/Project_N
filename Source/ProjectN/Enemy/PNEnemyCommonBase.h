// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/PNEnemyBase.h"
#include "Interface/EnemyCommonHpBarInterface.h"
#include "PNEnemyCommonBase.generated.h"

DECLARE_DELEGATE(FOnEnemyDead)

/**
 * 
 */
UCLASS()
class PROJECTN_API APNEnemyCommonBase : public APNEnemyBase, public IEnemyCommonHpBarInterface
{
	GENERATED_BODY()

public:
	APNEnemyCommonBase();

	/* AI Interface */
	virtual void NextComboAttack() override;

	/* EnemyApplyDamage Interface */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;
	
	/* EnemyCommonHpBar Interface */
	virtual void SetHpBar(class UEnemyHpBarWidget* InHpBar) override;

	virtual void SetDead() override;

	static FOnEnemyDead OnEnemyDead;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Effect")
	TObjectPtr<class UNiagaraComponent> ImpactNiagaraComop;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	TObjectPtr<class USphereComponent> FirstDetectSphereComp;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UEnemyRefWidgetComponent> HpBarWidgetComponent;

private:
	void DisplayDamageTextUI(float Damage);

private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UEnemyRefWidgetComponent> DamageTextWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<class UEnemyRefWidget> HpBarClass;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> DamagedTextClass;
};
