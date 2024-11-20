// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNBattleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Character/PNCharacterComboDataAsset.h"

UPNBattleSystemComponent::UPNBattleSystemComponent()
{
	static ConstructorHelpers::FObjectFinder<UPNCharacterComboDataAsset> ComboDataRef(TEXT("/Script/ProjectN.PNCharacterComboDataAsset'/Game/Project_N/Data/Character/DA_ComboAttack.DA_ComboAttack'"));
	if (ComboDataRef.Object)
	{
		ComboData = ComboDataRef.Object;
	}

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
	Anim->Montage_Play(ChargeMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndCharge);
	Anim->Montage_SetEndDelegate(MontageEnd, ChargeMontage);
}

void UPNBattleSystemComponent::EndCharge(UAnimMontage* Target, bool IsProperlyEnded)
{
	if (CurrentAttackState == EAttackState::ASCharge)
	{
		CurrentAttackState = EAttackState::ASIdle;
	}
}

void UPNBattleSystemComponent::Attack()
{
	switch (CurrentAttackState)
	{
	case EAttackState::ASIdle:
		UE_LOG(LogTemp, Display, TEXT("Charge"));
		Charge();
		break;
	case EAttackState::ASLight:
		if (!LightAttackTimer.IsValid())
			HasNextLightAttack = false;
		else
			HasNextLightAttack = true;
		break;
	}
}

void UPNBattleSystemComponent::HeavyAttack()
{
	if (CurrentLightAttackCombo == 1 || CurrentAttackState == EAttackState::ASHeavy)
	{
		CurrentAttackState = EAttackState::ASHeavy;

		//Anim->Montage_Stop(1.f, AttackMontage);
		
		if (CurrentHeavyAttackCombo == 0)
		{
			BeginHeavyAttack();
			return;
		}

		if (!HeavyAttackTimer.IsValid())
			HasNextHeavyAttack = false;
		else
			HasNextHeavyAttack = true;
	}
}

void UPNBattleSystemComponent::SuccessCharge()
{
	CurrentAttackState = EAttackState::ASCharge;

	Anim->Montage_JumpToSection(TEXT("ChargeBegin"), ChargeMontage);
}

void UPNBattleSystemComponent::FailCharge()
{
	CurrentAttackState = EAttackState::ASLight;

	Anim->Montage_Stop(0.1f, ChargeMontage);
	LightAttack();
}

void UPNBattleSystemComponent::LightAttack()
{
	CurrentLightAttackCombo = 1;
	Anim->Montage_Play(AttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndLightAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, AttackMontage);

	LightAttackTimer.Invalidate();
	SetTimerLightAttack();
}

void UPNBattleSystemComponent::EndLightAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	ensure(CurrentLightAttackCombo != 0);
	CurrentLightAttackCombo = 0;
	if (CurrentAttackState == EAttackState::ASLight)
	{
		CurrentAttackState = EAttackState::ASIdle;
	}
}

void UPNBattleSystemComponent::SetTimerLightAttack()
{
	int32 ComboIndex = CurrentLightAttackCombo - 1;

	float ComboEffectiveTime = (ComboData->EffectiveFrameCount[EAttackMontage::Light].FrameCounts[ComboIndex] / ComboData->FrameRate[EAttackMontage::Light]);
	if (ComboEffectiveTime > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(LightAttackTimer, this, &UPNBattleSystemComponent::CheckTimerLightAttack, ComboEffectiveTime, false);
	}
}

void UPNBattleSystemComponent::CheckTimerLightAttack()
{
	LightAttackTimer.Invalidate();
	if (HasNextLightAttack)
	{
		CurrentLightAttackCombo = FMath::Clamp(CurrentLightAttackCombo + 1, 1, ComboData->MaxCombo[EAttackMontage::Light]);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboData->SectionName[EAttackMontage::Light], CurrentLightAttackCombo);
		Anim->Montage_JumpToSection(NextSection, AttackMontage);

		SetTimerLightAttack();
		HasNextLightAttack = false;
	}
}

void UPNBattleSystemComponent::ChargeAttack()
{
	Anim->Montage_Play(ChargeAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndChargeAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, ChargeAttackMontage);
}

void UPNBattleSystemComponent::EndChargeAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	CurrentAttackState = EAttackState::ASIdle;
}


void UPNBattleSystemComponent::BeginHeavyAttack()
{
	CurrentHeavyAttackCombo = 1;
	Anim->Montage_Play(HeavyAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndHeavyAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, HeavyAttackMontage);

	HeavyAttackTimer.Invalidate();
	SetTimerHeavyAttack();
}

void UPNBattleSystemComponent::EndHeavyAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	ensure(CurrentHeavyAttackCombo != 0);
	CurrentHeavyAttackCombo = 0;
	CurrentAttackState = EAttackState::ASIdle;
}

void UPNBattleSystemComponent::SetTimerHeavyAttack()
{
	int32 ComboIndex = CurrentHeavyAttackCombo - 1;

	float ComboEffectiveTime = (ComboData->EffectiveFrameCount[EAttackMontage::Heavy].FrameCounts[ComboIndex] / ComboData->FrameRate[EAttackMontage::Heavy]);
	if (ComboEffectiveTime > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(HeavyAttackTimer, this, &UPNBattleSystemComponent::CheckTimerHeavyAttack, ComboEffectiveTime, false);
	}
}

void UPNBattleSystemComponent::CheckTimerHeavyAttack()
{
	HeavyAttackTimer.Invalidate();
	if (HasNextHeavyAttack)
	{
		CurrentHeavyAttackCombo = FMath::Clamp(CurrentHeavyAttackCombo + 1, 1, ComboData->MaxCombo[EAttackMontage::Heavy]);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboData->SectionName[EAttackMontage::Heavy], CurrentHeavyAttackCombo);
		Anim->Montage_JumpToSection(NextSection, HeavyAttackMontage);

		SetTimerHeavyAttack();
		HasNextHeavyAttack = false;
	}
}

