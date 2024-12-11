// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UBossStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UBossStatusWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	void UpdateHpBar(float NewHp);
	void SetMaxHp(float InMaxHp);

private:
	UPROPERTY()
	TObjectPtr<class UBossHpBarWidget> HpBar;
};
