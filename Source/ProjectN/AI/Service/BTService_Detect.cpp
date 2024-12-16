// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_Detect.h"
#include "AIController.h"
#include "Interface/AIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 0.5f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	if (Owner == nullptr) return;

	IAIInterface* Interface = Cast<IAIInterface>(Owner);
	if (Interface == nullptr) return;

	UWorld* World = Owner->GetWorld();
	if (World == nullptr) return;

	float Radius = Interface->GetDetectRadius();

	TArray<FOverlapResult> OverlapResults;
	FVector Origin = Owner->GetActorLocation();
	FCollisionQueryParams Params(NAME_None, false, Owner);
	DrawDebugSphere(World, Origin, Radius, 32, FColor::Red, false, 1.f);
	bool bHit = World->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(Radius), Params);
	if (bHit)
	{
		for (const FOverlapResult& OverlapResult : OverlapResults)
		{
			APawn* Target = Cast<APawn>(OverlapResult.GetActor());
			if (Target)
			{
				UE_LOG(LogTemp, Display, TEXT("Player 탐지"));
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Player 없는디?"));
			}
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Target);
			return;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Player 탐지 못함"));
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
}
