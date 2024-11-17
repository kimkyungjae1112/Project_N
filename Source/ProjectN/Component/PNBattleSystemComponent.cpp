// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNBattleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

UPNBattleSystemComponent::UPNBattleSystemComponent()
{
	CurrentAttackState = EAttackState::ASIdle;
}


void UPNBattleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = CastChecked<ACharacter>(GetOwner());
	Anim = Player->GetMesh()->GetAnimInstance();
	ensure(Anim);
}

void UPNBattleSystemComponent::Charge()
{
	Anim->Montage_Play(AttackMontage);
}

void UPNBattleSystemComponent::Attack()
{
}

void UPNBattleSystemComponent::ChargeAttack()
{
	UE_LOG(LogTemp, Display, TEXT("Charge Attack"));
}

void UPNBattleSystemComponent::LightAttack()
{
	UE_LOG(LogTemp, Display, TEXT("Light Attack"));
}

void UPNBattleSystemComponent::HeavyAttack()
{
	UE_LOG(LogTemp, Display, TEXT("Heavy Attack"));
}

void UPNBattleSystemComponent::SuccessCharge()
{
	Anim->Montage_JumpToSection(TEXT("ChargeBegin"), AttackMontage);
	CurrentAttackState = EAttackState::ASCharge;
}

void UPNBattleSystemComponent::FailCharge()
{
	Anim->Montage_JumpToSection(TEXT("LightAttack1"), AttackMontage);
	CurrentAttackState = EAttackState::ASLeft;
}



