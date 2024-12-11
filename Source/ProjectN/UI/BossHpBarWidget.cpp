// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BossHpBarWidget.h"
#include "Components/ProgressBar.h"

UBossHpBarWidget::UBossHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UBossHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar")));
	ensure(HpBar);
}

void UBossHpBarWidget::UpdateHpBar(float NewHp)
{
	HpBar->SetPercent(NewHp / MaxHp);
}

void UBossHpBarWidget::SetMaxHp(float InMaxHp)
{
	MaxHp = InMaxHp;
}
