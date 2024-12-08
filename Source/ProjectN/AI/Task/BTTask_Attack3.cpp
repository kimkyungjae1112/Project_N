// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Attack3.h"
#include "AIController.h"
#include "Interface/AIInterface.h"

UBTTask_Attack3::UBTTask_Attack3()
{
	NodeName = TEXT("Attack3");
}

EBTNodeResult::Type UBTTask_Attack3::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return EBTNodeResult::Failed;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	FOnAttack_3_Finished OnAttack_3_Finished;
	OnAttack_3_Finished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	Interface->SetAttack_3_Delegate(OnAttack_3_Finished);
	Interface->Attack_3();

	return EBTNodeResult::InProgress;
}
