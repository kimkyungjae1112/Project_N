// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UPlayerHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerHpBarWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateHpBar(float NewHp);
	void SetMaxHp(float InMaxHp);

private:
	UPROPERTY(VisibleAnywhere, Category = "HpBar")
	TObjectPtr<class UProgressBar> HpBar;

	float MaxHp;
};
