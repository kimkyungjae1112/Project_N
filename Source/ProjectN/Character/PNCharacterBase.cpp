// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PNCharacterBase.h"

APNCharacterBase::APNCharacterBase()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
}

void APNCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APNCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

