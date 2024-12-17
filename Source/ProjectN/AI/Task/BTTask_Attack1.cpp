// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_Attack1.h"
#include "AIController.h"
#include "Interface/AIInterface.h"

UBTTask_Attack1::UBTTask_Attack1()
{
	NodeName = TEXT("Attack1");
}

EBTNodeResult::Type UBTTask_Attack1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return EBTNodeResult::Failed;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return EBTNodeResult::Failed;

	FOnAttack_1_Finished OnAttack_1_Finished;
	OnAttack_1_Finished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	Interface->SetAttack_1_Delegate(OnAttack_1_Finished);
	Interface->Attack_1();
	UE_LOG(LogTemp, Display, TEXT("공격"));

	return EBTNodeResult::InProgress;
}
