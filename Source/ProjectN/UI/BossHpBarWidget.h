// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UBossHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBossHpBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateHpBar(float NewHp);
	void SetMaxHp(float InMaxHp);

private:
	UPROPERTY(VisibleAnywhere, Category = "HpBar")
	TObjectPtr<class UProgressBar> HpBar;

	float MaxHp;
};
