// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponSocketCarryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponSocketCarryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTN_API IWeaponSocketCarryInterface
{
	GENERATED_BODY()

public:
	virtual class USkeletalMeshComponent* GetWeaponMeshComponent() = 0;
};
