// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyBase.h"
#include "AI/Controller/PNAIControllerBase.h"

APNEnemyBase::APNEnemyBase()
{
	StatComp = CreateDefaultSubobject<UPNEnemyStatComponent>(TEXT("Stat Component"));
	StatComp->OnHpZero.AddUObject(this, &APNEnemyBase::SetDead);
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
}

void APNEnemyBase::SetDead()
{
	GetAIController()->StopAI();
}
