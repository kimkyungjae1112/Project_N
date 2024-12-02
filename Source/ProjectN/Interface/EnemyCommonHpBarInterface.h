// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyCommonHpBarInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyCommonHpBarInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTN_API IEnemyCommonHpBarInterface
{
	GENERATED_BODY()

public:
	virtual void SetHpBar(class UEnemyHpBarWidget* InHpBar) = 0;
};
