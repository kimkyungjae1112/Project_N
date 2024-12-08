// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Attack4.h"
#include "AIController.h"
#include "Interface/AIInterface.h"

UBTTask_Attack4::UBTTask_Attack4()
{
	NodeName = TEXT("Attack4");
}

EBTNodeResult::Type UBTTask_Attack4::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return EBTNodeResult::Failed;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	FOnAttack_4_Finished OnAttack_4_Finished;
	OnAttack_4_Finished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	Interface->SetAttack_4_Delegate(OnAttack_4_Finished);
	Interface->Attack_4();

	return EBTNodeResult::InProgress;
}
