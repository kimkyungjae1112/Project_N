// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameManagerSubsystem.h"
#include "Enemy/PNEnemyCommonBase.h"

UGameManagerSubsystem::UGameManagerSubsystem()
{
	APNEnemyCommonBase::OnEnemyDead.BindUObject(this, &UGameManagerSubsystem::DeadCountEnemy);
}

void UGameManagerSubsystem::DeadCountEnemy()
{
	UE_LOG(LogTemp, Display, TEXT("싱글톤"));
	DeadCountEnemyNum++;
	OnEnemyDeadSign.ExecuteIfBound();

	if (DeadCountEnemyNum >= 2)
	{
		OnCompleteStageSign.Broadcast();
	}
}
