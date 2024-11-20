// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_DetectDistanceToTarget.h"
#include "AIController.h"
#include "Interface/AIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_DetectDistanceToTarget::UBTService_DetectDistanceToTarget()
{
	NodeName = TEXT("Detect Distance To Target");
	Interval = 0.5f;
}

void UBTService_DetectDistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target == nullptr) return;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return;

	float Distance = FVector::Distance(Owner->GetActorLocation(), Target->GetActorLocation());
	if (Interface->GetMeleeAttackInRange() >= Distance)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("TargetInMeleeAttack"), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("TargetInMeleeAttack"), false);
	}
}
