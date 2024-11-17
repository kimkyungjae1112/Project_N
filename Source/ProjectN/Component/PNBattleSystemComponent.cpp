// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNBattleSystemComponent.h"

UPNBattleSystemComponent::UPNBattleSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPNBattleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPNBattleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

