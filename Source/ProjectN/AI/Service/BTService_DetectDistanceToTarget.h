// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectDistanceToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UBTService_DetectDistanceToTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_DetectDistanceToTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
