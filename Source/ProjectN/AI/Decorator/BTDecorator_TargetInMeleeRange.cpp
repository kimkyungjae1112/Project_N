// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTDecorator_TargetInMeleeRange.h"
#include "AIController.h"
#include "Interface/AIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_TargetInMeleeRange::UBTDecorator_TargetInMeleeRange()
{
	NodeName = TEXT("Target Is In Melee Range");
}

bool UBTDecorator_TargetInMeleeRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool SuperResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return false;

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target == nullptr) return false;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return false;

	float Distance = FVector::Distance(Owner->GetActorLocation(), Target->GetActorLocation());
	UE_LOG(LogTemp, Display, TEXT("Distance : %f"), Distance);
	return Interface->GetMeleeAttackInRange() >= Distance;
}
