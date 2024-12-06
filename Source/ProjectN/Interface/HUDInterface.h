// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTN_API IHUDInterface
{
	GENERATED_BODY()

public:
	virtual void SetupHUD_Widget(class UPlayerHUDWidget* InHUDWidget) = 0;
};
