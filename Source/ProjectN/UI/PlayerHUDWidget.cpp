// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDWidget.h"
#include "UI/PlayerHpBarWidget.h"
#include "UI/PlayerEnergyBarWidget.h"
#include "Interface/HUDInterface.h"

UPlayerHUDWidget::UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UPlayerHpBarWidget>(GetWidgetFromName(TEXT("WBP_HpBar")));
	ensure(HpBar);

	EnergyBar = Cast<UPlayerEnergyBarWidget>(GetWidgetFromName(TEXT("WBP_EnergyBar")));
	ensure(EnergyBar);

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

void UPlayerHUDWidget::UpdateEnergyBar(float UseEnergy)
{
	EnergyBar->UpdateEnergyBar(UseEnergy);
}

void UPlayerHUDWidget::SetMaxHp(float InMaxHp)
{
	HpBar->SetMaxHp(InMaxHp);
}

void UPlayerHUDWidget::SetMaxEnergy(float InMaxEnergy)
{
	EnergyBar->SetMaxEnergy(InMaxEnergy);
}
