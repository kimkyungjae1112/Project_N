// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEnergyBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UPlayerEnergyBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerEnergyBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateEnergyBar(float UseEnergy);
	void SetMaxEnergy(float InMaxEnergy);

private:
	UPROPERTY(VisibleAnywhere, Category = "HpBar")
	TObjectPtr<class UProgressBar> EnergyBar;

	float MaxEnergy;

};
