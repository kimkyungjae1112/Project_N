// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"
#include "UI/PlayerHpBarWidget.h"
#include "Interface/HUDInterface.h"

UPlayerHUDWidget::UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.f;
}

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UPlayerHpBarWidget>(GetWidgetFromName(TEXT("WBP_HpBar")));
	ensure(HpBar);

	IHUDInterface* Interface = Cast<IHUDInterface>(GetOwningPlayerPawn());
	if (Interface)
	{
		Interface->SetupHUD_Widget(this);
	}
}

void UPlayerHUDWidget::UpdateHpBar(float NewHp)
{
	HpBar->UpdateHpBar(NewHp);
}

void UPlayerHUDWidget::SetMaxHp(float InMaxHp)
{
	MaxHp = InMaxHp;
	HpBar->SetMaxHp(MaxHp);
}
