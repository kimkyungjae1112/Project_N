// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerApplyDamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerApplyDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTN_API IPlayerApplyDamageInterface
{
	GENERATED_BODY()

public:
	virtual void HitReaction() = 0;
};
