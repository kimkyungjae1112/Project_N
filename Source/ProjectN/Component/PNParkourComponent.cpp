// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNParkourComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UPNParkourComponent::UPNParkourComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPNParkourComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = CastChecked<ACharacter>(GetOwner());
}


void UPNParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPNParkourComponent::Run()
{
	Character->GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void UPNParkourComponent::Walk()
{
	Character->GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

