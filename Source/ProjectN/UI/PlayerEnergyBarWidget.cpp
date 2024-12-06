// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerEnergyBarWidget.h"
#include "Components/ProgressBar.h"

UPlayerEnergyBarWidget::UPlayerEnergyBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxEnergy = -1.f;
}

void UPlayerEnergyBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EnergyBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_EnergyBar")));
	ensure(EnergyBar);
}

void UPlayerEnergyBarWidget::UpdateEnergyBar(float UseEnergy)
{
	EnergyBar->SetPercent(UseEnergy);
}

void UPlayerEnergyBarWidget::SetMaxEnergy(float InMaxEnergy)
{
	MaxEnergy = InMaxEnergy;
}
