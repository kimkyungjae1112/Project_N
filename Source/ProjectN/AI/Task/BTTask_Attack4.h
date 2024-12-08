// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack4.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UBTTask_Attack4 : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack4();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
