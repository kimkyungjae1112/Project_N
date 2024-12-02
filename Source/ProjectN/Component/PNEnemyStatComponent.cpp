// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNEnemyStatComponent.h"

UPNEnemyStatComponent::UPNEnemyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHp = 1000.f;
	Hp = MaxHp;
}

void UPNEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UPNEnemyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPNEnemyStatComponent::ApplyDamage(float InDamage)
{
	float ActualDamage = FMath::Clamp(InDamage, 0, InDamage);
	float PrevHp = Hp;

	SetHp(PrevHp - ActualDamage);
	if (Hp < KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
}

void UPNEnemyStatComponent::SetHp(float NewHp)
{
	Hp = NewHp;
	OnHpChanged.Broadcast(Hp);
}

