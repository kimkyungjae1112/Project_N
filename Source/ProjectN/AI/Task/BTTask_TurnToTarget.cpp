// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Task/BTTask_TurnToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn To Target");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type SuperResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return EBTNodeResult::Failed;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target == nullptr) return EBTNodeResult::Failed;

	FVector Direct = Target->GetActorLocation() - Owner->GetActorLocation();
	Direct.Z = 0.f;
	FRotator Rot = FRotationMatrix::MakeFromX(Direct).Rotator();
	Owner->SetActorRotation(FMath::RInterpTo(Owner->GetActorRotation(), Rot, GetWorld()->GetDeltaSeconds(), 2.f));

	return EBTNodeResult::Succeeded;
}
