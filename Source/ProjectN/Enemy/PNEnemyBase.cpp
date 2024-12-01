// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyBase.h"
#include "AI/Controller/PNAIControllerBase.h"

float APNEnemyBase::GetMeleeAttackInRange()
{
	return 350.0f;
}

void APNEnemyBase::Attack_1()
{
}

void APNEnemyBase::Attack_2()
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

APNAIControllerBase* APNEnemyBase::GetAIController()
{
	return Cast<APNAIControllerBase>(GetController());
}

void APNEnemyBase::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
}
