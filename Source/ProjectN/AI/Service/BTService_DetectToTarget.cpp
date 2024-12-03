// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_DetectToTarget.h"
#include "AIController.h"
#include "Interface/AIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"

UBTService_DetectToTarget::UBTService_DetectToTarget()
{
	NodeName = TEXT("Detect To Target");
	Interval = 0.5f;
}

void UBTService_DetectToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return;

	float Radius = Interface->GetDetectRadius();

	TArray<FOverlapResult> OverlapResults;
	FVector Origin = Owner->GetActorLocation();
	FCollisionQueryParams Params(NAME_None, false, Owner);
	bool bHit = Owner->GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Radius), Params);
	if (bHit)
	{
		for (const FOverlapResult& OverlapResult : OverlapResults)
		{
			APawn* Target = Cast<APawn>(OverlapResult.GetActor());
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Target);
			return;
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
}
