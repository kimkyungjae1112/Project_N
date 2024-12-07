// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNPlayerStatComponent.h"

UPNPlayerStatComponent::UPNPlayerStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHp = 1000.f;
	Hp = MaxHp;

	MaxEnergy = 100.f;
	Energy = MaxEnergy;
}

void UPNPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPNPlayerStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Energy < MaxEnergy - KINDA_SMALL_NUMBER)
	{
		float PrevEnergy = FMath::Clamp(Energy + DeltaTime * 7.f, 0, MaxEnergy);
		SetEnergy(PrevEnergy);
	}
}

void UPNPlayerStatComponent::ApplyDamage(float InDamage)
{
	float ActualDamage = FMath::Clamp(InDamage, 0, InDamage);
	float PrevHp = Hp;

	SetHp(PrevHp - ActualDamage);
	if (Hp < KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
}

void UPNPlayerStatComponent::ApplyEnergy(float InEnergy)
{
	float ActualEnergy = FMath::Clamp(InEnergy, 0, InEnergy);
	float PrevEnergy = Energy;

	SetEnergy(PrevEnergy - ActualEnergy);
	/*if (Energy < KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}*/
}

void UPNPlayerStatComponent::SetEnergy(float InEnergy)
{
	Energy = InEnergy;
	OnEnergyChanged.Broadcast(Energy);
}

void UPNPlayerStatComponent::SetHp(float NewHp)
{
	Hp = NewHp;
	OnHpChanged.Broadcast(Hp);
}

