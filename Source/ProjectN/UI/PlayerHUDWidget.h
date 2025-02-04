// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateHpBar(float NewHp);
	void UpdateEnergyBar(float UseEnergy);
	void SetMaxHp(float InMaxHp);
	void SetMaxEnergy(float InMaxEnergy);

private:
	UPROPERTY(VisibleAnywhere, Category = "HpBar")
	TObjectPtr<class UPlayerHpBarWidget> HpBar;

	UPROPERTY(VisibleAnywhere, Category = "EnergyBar")
	TObjectPtr<class UPlayerEnergyBarWidget> EnergyBar;

};
