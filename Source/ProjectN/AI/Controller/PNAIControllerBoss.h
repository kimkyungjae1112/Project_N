// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/PNAIControllerBase.h"
#include "PNAIControllerBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNAIControllerBoss : public APNAIControllerBase
{
	GENERATED_BODY()

public:
	APNAIControllerBoss();
	
protected:
	virtual void BeginPlay() override;

};
