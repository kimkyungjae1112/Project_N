// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FocusOnTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UBTService_FocusOnTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_FocusOnTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
