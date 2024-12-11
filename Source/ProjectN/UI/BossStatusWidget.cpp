// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BossStatusWidget.h"
#include "UI/BossHpBarWidget.h"

UBossStatusWidget::UBossStatusWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UBossStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	HpBar = Cast<UBossHpBarWidget>(GetWidgetFromName(TEXT("WBP_BossHpBar")));
	ensure(HpBar);
}

void UBossStatusWidget::UpdateHpBar(float NewHp)
{
	HpBar->UpdateHpBar(NewHp);
}

void UBossStatusWidget::SetMaxHp(float InMaxHp)
{
	HpBar->SetMaxHp(InMaxHp);
}


