// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Interface/EnemyCommonHpBarInterface.h"

UEnemyHpBarWidget::UEnemyHpBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UEnemyHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));
	ensure(HpBar);

	IEnemyCommonHpBarInterface* Interface = Cast<IEnemyCommonHpBarInterface>(OwningActor);
	if (Interface)
	{
		Interface->SetHpBar(this);
	}
}

void UEnemyHpBarWidget::UpdateHpBar(float NewHp)
{
	HpBar->SetPercent(NewHp / MaxHp);
}

void UEnemyHpBarWidget::SetMaxHp(float InMaxHp)
{
	MaxHp = InMaxHp;
}
