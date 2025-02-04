// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNBattleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Animation/PNAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Character/PNCharacterComboDataAsset.h"
#include "Interface/EnemyApplyDamageInterface.h"
#include "Blueprint/UserWidget.h"
#include "MotionWarpingComponent.h"
#include "Component/PNPlayerStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PNPlayerController.h"

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
	StatComp = GetOwner()->GetComponentByClass<UPNPlayerStatComponent>();
}

void UPNBattleSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//구현 취소
	/*DetectEnemyForAssassination();
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
	}*/
}

void UPNBattleSystemComponent::Charge()
{
	if (!Anim->Montage_IsPlaying(ChargeMontage))
	{
		Anim->Montage_Play(ChargeMontage);
	}

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

void UPNBattleSystemComponent::NoCharge()
{
	Anim->Montage_Stop(0.3f, ChargeMontage);

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
	StatComp->ApplyEnergy(StatComp->UseLightAttackEnergy());
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
		StatComp->ApplyEnergy(StatComp->UseLightAttackEnergy());
		CurrentLightAttackCombo = FMath::Clamp(CurrentLightAttackCombo + 1, 1, ComboData->MaxCombo[EAttackMontage::Light]);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboData->SectionName[EAttackMontage::Light], CurrentLightAttackCombo);
		Anim->Montage_JumpToSection(NextSection, AttackMontage);

		SetTimerLightAttack();
		HasNextLightAttack = false;
	}
}

void UPNBattleSystemComponent::ChargeAttack()
{
	StatComp->ApplyEnergy(15.f);
	Anim->Montage_Play(ChargeAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndChargeAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, ChargeAttackMontage);
}

void UPNBattleSystemComponent::BeginDashAttack()
{
	if (bIsDashAttacking) return;
	bIsDashAttacking = true;

	CurrentAttackState = EAttackState::ASDash;

	StatComp->ApplyEnergy(StatComp->UseDashAttackEnergy());
	Anim->Montage_Play(DashAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndDashAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, DashAttackMontage);
}

void UPNBattleSystemComponent::BeginAssassinationAttack()
{
	if (!bCanAssassination) return;

	StatComp->ApplyEnergy(20.f);
	AssassinationMotionWarpSet();
	Anim->Montage_Play(AssassinationMontage);
}

void UPNBattleSystemComponent::BeginBlock()
{
	UPNAnimInstance* PNAnim = Cast<UPNAnimInstance>(Anim);

	PNAnim->bIsBlock = true;
}

void UPNBattleSystemComponent::EndBlock()
{
	UPNAnimInstance* PNAnim = Cast<UPNAnimInstance>(Anim);

	PNAnim->bIsBlock = false;
}

void UPNBattleSystemComponent::BeginBlockAttacked()
{
	StatComp->ApplyEnergy(5.f);
	Anim->Montage_Play(BlockAttackedMontage);
	Init();

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndBlockAttacked);
	Anim->Montage_SetEndDelegate(MontageEnd, BlockAttackedMontage);
}

void UPNBattleSystemComponent::BeginAttacked()
{
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	Anim->Montage_Play(AttackedMontage);
	Init();

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndAttacked);
	Anim->Montage_SetEndDelegate(MontageEnd, AttackedMontage);
}

void UPNBattleSystemComponent::BeginKnockBackAttacked()
{
	Init();
	Anim->Montage_Play(KnockBackMontage);
}

void UPNBattleSystemComponent::BeginChangeNonCombat()
{
	UPNAnimInstance* PNAnim = Cast<UPNAnimInstance>(Anim);

	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndChangeNonCombat);

	PNAnim->bIsNoWeapon = ~PNAnim->bIsNoWeapon;
	if (PNAnim->bIsNoWeapon)
	{
		PNAnim->Montage_Play(NonWeaponMontage);
		Anim->Montage_SetEndDelegate(MontageEnd, NonWeaponMontage);
	}
	else
	{
		PNAnim->Montage_Play(WeaponMontage);
		Anim->Montage_SetEndDelegate(MontageEnd, WeaponMontage);
	}

	
	
}

void UPNBattleSystemComponent::BeginStun()
{
	if (Anim->Montage_IsPlaying(StunMontage)) return;
	Player->EnableInput(Cast<APNPlayerController>(GetWorld()->GetFirstPlayerController()));
	Anim->Montage_Play(StunMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNBattleSystemComponent::EndStun);
	Anim->Montage_SetEndDelegate(MontageEnd, StunMontage);
}

void UPNBattleSystemComponent::EndChargeAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	CurrentAttackState = EAttackState::ASIdle;
}

void UPNBattleSystemComponent::EndDashAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	CurrentAttackState = EAttackState::ASIdle;
	bIsDashAttacking = false;
	InitBehaviorState.Broadcast();
}

void UPNBattleSystemComponent::DetectEnemyForAssassination()
{
	if (MakeSweepTrace())
	{
		AActor* TargetEnemy = AssassinationedResult.GetActor();
		FVector TargetOrigin = TargetEnemy->GetActorLocation();
		FVector TargetForward = TargetEnemy->GetActorForwardVector();

		FVector PlayerForward = Player->GetActorForwardVector();


		double CosineValue = FMath::Cos(FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TargetForward, PlayerForward))));
		if (CosineValue > 0.f && CosineValue <= 1.f)
		{
			bCanAssassination = true;
		}
	}
	else
	{
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

	return GetWorld()->SweepSingleByChannel(AssassinationedResult, Origin, End, Quat, ECC_GameTraceChannel2, FCollisionShape::MakeCapsule(CapsuleExtent), Params);
}

void UPNBattleSystemComponent::AssassinationMotionWarpSet()
{
	AActor* TargetEnemy = AssassinationedResult.GetActor();
	if (!TargetEnemy) return;

	FVector TargetOrigin = TargetEnemy->GetActorLocation();
	FVector TargetForward = TargetEnemy->GetActorForwardVector();
	FVector TargetLoc = TargetOrigin + (-TargetForward * 150.f);
	
	Player->GetComponentByClass<UMotionWarpingComponent>()->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("Assassination"), TargetLoc, TargetForward.Rotation());
}

void UPNBattleSystemComponent::BeginHeavyAttack()
{
	CurrentHeavyAttackCombo = 1;
	StatComp->ApplyEnergy(StatComp->UseHeavyAttackEnergy());
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
		StatComp->ApplyEnergy(StatComp->UseHeavyAttackEnergy());
		CurrentHeavyAttackCombo = FMath::Clamp(CurrentHeavyAttackCombo + 1, 1, ComboData->MaxCombo[EAttackMontage::Heavy]);
		FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboData->SectionName[EAttackMontage::Heavy], CurrentHeavyAttackCombo);
		Anim->Montage_JumpToSection(NextSection, HeavyAttackMontage);

		SetTimerHeavyAttack();
		HasNextHeavyAttack = false;
	}
}

void UPNBattleSystemComponent::EndBlockAttacked(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void UPNBattleSystemComponent::EndAttacked(UAnimMontage* Target, bool IsProperlyEnded)
{
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UPNBattleSystemComponent::EndKnockBackAttacked(UAnimMontage* Target, bool IsProperlyEnded)
{
}

void UPNBattleSystemComponent::EndChangeNonCombat(UAnimMontage* Target, bool IsProperlyEnded)
{
	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UPNBattleSystemComponent::EndStun(UAnimMontage* Target, bool IsProperlyEnded)
{
	StatComp->SetEnergyFlag();
	Player->EnableInput(Cast<APNPlayerController>(GetWorld()->GetFirstPlayerController()));
}

void UPNBattleSystemComponent::Init()
{
	CurrentAttackState = EAttackState::ASIdle;
	CurrentLightAttackCombo = 0;
	CurrentHeavyAttackCombo = 0;

}
