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

		bool DebugFlag = false;
		if (DebugFlag)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack1"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack2"), true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack3"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack4"), false);
			return;
		}

		int32 RandomIndex = FMath::RandRange(0, 10);
		if (RandomIndex >= 0 && RandomIndex <= 4)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack1"), true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack2"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack3"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack4"), false);
		}
		else if (RandomIndex >= 5 && RandomIndex <= 6)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack1"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack2"), true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack3"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack4"), false);
		}
		else if (RandomIndex >= 7 && RandomIndex <= 8)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack1"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack2"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack3"), true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack4"), false);
		}
		else if (RandomIndex >= 9 && RandomIndex <= 10)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack1"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack2"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack3"), false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("MeleeAttack4"), true);
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("TargetInMeleeAttack"), false);


		if (Distance >= 800.f)
		{
			int32 RandomIndex = FMath::RandRange(0, 10);
			if (RandomIndex >= 0 && RandomIndex <= 3)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack1"), true);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack2"), false);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack3"), false);
			}
			else if (RandomIndex >= 4 && RandomIndex <= 6)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack1"), false);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack2"), true);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack3"), false);
			}
			else if (RandomIndex >= 7 && RandomIndex <= 10)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack1"), false);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack2"), false);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("RangedAttack3"), true);
			}
			
		}
	}
}
