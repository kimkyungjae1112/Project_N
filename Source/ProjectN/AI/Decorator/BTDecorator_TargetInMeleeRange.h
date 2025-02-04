// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_TargetInMeleeRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UBTDecorator_TargetInMeleeRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_TargetInMeleeRange();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
