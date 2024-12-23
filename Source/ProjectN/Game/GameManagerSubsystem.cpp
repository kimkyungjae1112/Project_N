// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameManagerSubsystem.h"
#include "Enemy/PNEnemyCommonBase.h"

UGameManagerSubsystem::UGameManagerSubsystem()
{
	APNEnemyCommonBase::OnEnemyDead.BindUObject(this, &UGameManagerSubsystem::DeadCountEnemy);
}

void UGameManagerSubsystem::DeadCountEnemy()
{
	DeadCountEnemyNum++;
	OnEnemyDeadSign.ExecuteIfBound();

	if (DeadCountEnemyNum >= 5)
	{
		OnCompleteStageSign.Broadcast();
	}
}
