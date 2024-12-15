// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManagerSubsystem.generated.h"

DECLARE_DELEGATE(FOnEnemyDeadSign)
DECLARE_MULTICAST_DELEGATE(FOnCompleteStageSign)
/**
 * 
 */
UCLASS()
class PROJECTN_API UGameManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UGameManagerSubsystem();

	FORCEINLINE int32 GetDeadCountEnemyNum() { return DeadCountEnemyNum; }

	FOnEnemyDeadSign OnEnemyDeadSign;
	FOnCompleteStageSign OnCompleteStageSign;

private:
	void DeadCountEnemy();

	int32 DeadCountEnemyNum = 0;
};
