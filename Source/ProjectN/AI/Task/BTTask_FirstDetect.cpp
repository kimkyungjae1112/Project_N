// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_FirstDetect.h"
#include "AIController.h"
#include "Interface/AIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FirstDetect::UBTTask_FirstDetect()
{
	NodeName = TEXT("First Detect");
}

EBTNodeResult::Type UBTTask_FirstDetect::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return EBTNodeResult::Failed;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface)
	{
		Interface->FirstDetectPlayer();
	}

	return EBTNodeResult::Succeeded;
}
