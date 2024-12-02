// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNBattleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Character/PNCharacterComboDataAsset.h"
#include "Interface/EnemyApplyDamageInterface.h"
#include "Blueprint/UserWidget.h"

UPNBattleSystemComponent::UPNBattleSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

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

	AssassinationUI = CreateWidget(GetWorld(), AssassinationUIClass);
}

void UPNBattleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DetectEnemyForAssassination();
	if (bCanAssassination)
	{
		if (AssassinationUI && !AssassinationUI->IsInViewport())
		{
			AssassinationUI->AddToViewport();
		}
	}
	else
	{
		if (AssassinationUI->IsInViewport())
		{
			AssassinationUI->RemoveFromViewport();
		}
	}
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

void UPNBattleSystemComponent::BeginDashAttack()
{
	if (bIsDashAttacking) return;
	bIsDashAttacking = true;
	Anim->Montage_Play(DashAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndDashAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, DashAttackMontage);
}

void UPNBattleSystemComponent::BeginAssassinationAttack()
{
	if (!bCanAssassination) return;
	Anim->Montage_Play(AssassinationMontage);
}

void UPNBattleSystemComponent::EndChargeAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	CurrentAttackState = EAttackState::ASIdle;
}

void UPNBattleSystemComponent::EndDashAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	bIsDashAttacking = false;
	InitBehaviorState.Broadcast();
}

void UPNBattleSystemComponent::DetectEnemyForAssassination()
{
	if (MakeSweepTrace())
	{
		UE_LOG(LogTemp, Display, TEXT("성공?"));
		bCanAssassination = true;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("실패?"));
		bCanAssassination = false;
	}
}

bool UPNBattleSystemComponent::MakeSweepTrace()
{
	float Range = 300.f;
	FVector Origin = Player->GetActorLocation() + FVector(0.f, 0.f, Player->BaseEyeHeight);
	FVector End = Origin + Player->GetActorForwardVector() * Range;
	FQuat Quat = FRotationMatrix::MakeFromZ(End).ToQuat();
	FVector CapsuleExtent = FVector(10.f, 50.f, 10.f);

	FCollisionQueryParams Params(NAME_None, false, Player);

	// 캡슐의 중심 위치
	FVector CapsuleCenter = (Origin + End) / 2.f;

	// 캡슐 반지름과 반높이
	float CapsuleRadius = CapsuleExtent.Y; // Y축이 반지름
	float CapsuleHalfHeight = Range / 2.f + CapsuleExtent.Z; // Z축이 반높이

	// 캡슐을 그리기
	DrawDebugCapsule(GetWorld(), CapsuleCenter, CapsuleHalfHeight, CapsuleRadius, Quat, FColor::Blue, false);

	return GetWorld()->SweepSingleByChannel(AssassinationedResult, Origin, End, Quat, ECC_GameTraceChannel2, FCollisionShape::MakeCapsule(CapsuleExtent), Params);
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
