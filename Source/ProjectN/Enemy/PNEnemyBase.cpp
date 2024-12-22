// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyBase.h"
#include "AI/Controller/PNAIControllerBase.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

APNEnemyBase::APNEnemyBase()
{
	StatComp = CreateDefaultSubobject<UPNEnemyStatComponent>(TEXT("Stat Component"));
	StatComp->OnHpZero.AddUObject(this, &APNEnemyBase::SetDead);

	static ConstructorHelpers::FObjectFinder<USoundCue> HitSound1Ref(TEXT("/Script/Engine.SoundCue'/Game/Project_N/Sound/Metallic_Impact_Sword_Attack_With_Blood_01_Cue.Metallic_Impact_Sword_Attack_With_Blood_01_Cue'"));
	if (HitSound1Ref.Object)
	{
		HitSounds.Add(HitSound1Ref.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> HitSound2Ref(TEXT("/Script/Engine.SoundCue'/Game/Project_N/Sound/Metallic_Impact_Sword_Attack_With_Blood_02_Cue.Metallic_Impact_Sword_Attack_With_Blood_02_Cue'"));
	if (HitSound2Ref.Object)
	{
		HitSounds.Add(HitSound2Ref.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> HitSound3Ref(TEXT("/Script/Engine.SoundCue'/Game/Project_N/Sound/Metallic_Impact_Sword_Attack_With_Blood_03_Cue.Metallic_Impact_Sword_Attack_With_Blood_03_Cue'"));
	if (HitSound3Ref.Object)
	{
		HitSounds.Add(HitSound3Ref.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> HitSound4Ref(TEXT("/Script/Engine.SoundCue'/Game/Project_N/Sound/Metallic_Impact_Sword_Attack_With_Blood_04_Cue.Metallic_Impact_Sword_Attack_With_Blood_04_Cue'"));
	if (HitSound4Ref.Object)
	{
		HitSounds.Add(HitSound4Ref.Object);
	}
	static ConstructorHelpers::FObjectFinder<USoundCue> HitSound5Ref(TEXT("/Script/Engine.SoundCue'/Game/Project_N/Sound/Metallic_Impact_Sword_Attack_With_Blood_05_Cue.Metallic_Impact_Sword_Attack_With_Blood_05_Cue'"));
	if (HitSound5Ref.Object)
	{
		HitSounds.Add(HitSound5Ref.Object);
	}
}

float APNEnemyBase::GetMeleeAttackInRange()
{
	return 350.0f;
}

float APNEnemyBase::GetDetectRadius()
{
	return 1000.0f;
}

void APNEnemyBase::Attack_1()
{
}

void APNEnemyBase::Attack_2()
{
}

void APNEnemyBase::Attack_3()
{
}

void APNEnemyBase::Attack_4()
{
}

void APNEnemyBase::Attack_5()
{
}

void APNEnemyBase::Attack_6()
{
}

void APNEnemyBase::SetAttack_1_Delegate(const FOnAttack_1_Finished& InOnAttack_1_Finished)
{
	OnAttack_1_Finished = InOnAttack_1_Finished;
}

void APNEnemyBase::SetAttack_2_Delegate(const FOnAttack_2_Finished& InOnAttack_2_Finished)
{
	OnAttack_2_Finished = InOnAttack_2_Finished;
}

void APNEnemyBase::SetAttack_3_Delegate(const FOnAttack_3_Finished& InOnAttack_3_Finished)
{
	OnAttack_3_Finished = InOnAttack_3_Finished;
}

void APNEnemyBase::SetAttack_4_Delegate(const FOnAttack_4_Finished& InOnAttack_4_Finished)
{
	OnAttack_4_Finished = InOnAttack_4_Finished;
}

void APNEnemyBase::SetAttack_5_Delegate(const FOnAttack_5_Finished& InOnAttack_5_Finished)
{
	OnAttack_5_Finished = InOnAttack_5_Finished;
}

void APNEnemyBase::SetAttack_6_Delegate(const FOnAttack_6_Finished& InOnAttack_6_Finished)
{
	OnAttack_6_Finished = InOnAttack_6_Finished;
}

APNAIControllerBase* APNEnemyBase::GetAIController()
{
	return Cast<APNAIControllerBase>(GetController());
}

void APNEnemyBase::NextComboAttack()
{
}

void APNEnemyBase::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	int32 Index = FMath::RandRange(0, 4);
	UGameplayStatics::PlaySoundAtLocation(this, HitSounds[Index], ImpactLocation);
}

void APNEnemyBase::SetDead()
{
	GetAIController()->StopAI();
}
