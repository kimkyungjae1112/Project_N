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

	/* 대미지 전달 */
	virtual void ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation) override;

	/* UI */
	virtual void SetHpBar(class UEnemyHpBarWidget* InHpBar) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UEnemyRefWidgetComponent> HpBarWidgetComponent;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<class UEnemyRefWidget> HpBarClass;
};