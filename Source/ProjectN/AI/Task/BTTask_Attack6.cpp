// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Attack6.h"
#include "AIController.h"
#include "Interface/AIInterface.h"

UBTTask_Attack6::UBTTask_Attack6()
{
	NodeName = TEXT("Attack6");
}

EBTNodeResult::Type UBTTask_Attack6::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return EBTNodeResult::Failed;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	FOnAttack_6_Finished OnAttack_6_Finished;
	OnAttack_6_Finished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	Interface->SetAttack_6_Delegate(OnAttack_6_Finished);
	Interface->Attack_6();

	return EBTNodeResult::InProgress;
}
