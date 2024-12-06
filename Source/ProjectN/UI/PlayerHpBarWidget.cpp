// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHpBarWidget.h"
#include "Components/ProgressBar.h"

UPlayerHpBarWidget::UPlayerHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UPlayerHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar")));
	ensure(HpBar);
}

void UPlayerHpBarWidget::UpdateHpBar(float NewHp)
{
	HpBar->SetPercent(NewHp / MaxHp);
}

void UPlayerHpBarWidget::SetMaxHp(float InMaxHp)
{
	MaxHp = InMaxHp;
}
