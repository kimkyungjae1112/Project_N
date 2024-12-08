// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Attack2.h"
#include "AIController.h"
#include "Interface/AIInterface.h"

UBTTask_Attack2::UBTTask_Attack2()
{
	NodeName = TEXT("Attack2");
}

EBTNodeResult::Type UBTTask_Attack2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return EBTNodeResult::Failed;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	FOnAttack_2_Finished OnAttack_2_Finished;
	OnAttack_2_Finished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	Interface->SetAttack_2_Delegate(OnAttack_2_Finished);
	Interface->Attack_2();

	return EBTNodeResult::InProgress;
}