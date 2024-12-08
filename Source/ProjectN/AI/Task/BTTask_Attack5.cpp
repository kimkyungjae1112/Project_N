// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Attack5.h"
#include "AIController.h"
#include "Interface/AIInterface.h"

UBTTask_Attack5::UBTTask_Attack5()
{
	NodeName = TEXT("Attack5");
}

EBTNodeResult::Type UBTTask_Attack5::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return EBTNodeResult::Failed;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	FOnAttack_5_Finished OnAttack_5_Finished;
	OnAttack_5_Finished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	Interface->SetAttack_5_Delegate(OnAttack_5_Finished);
	Interface->Attack_5();

	return EBTNodeResult::InProgress;
}

