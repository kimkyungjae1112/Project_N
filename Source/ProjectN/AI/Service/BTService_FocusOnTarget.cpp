// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_FocusOnTarget.h"
#include "AIController.h"
#include "Interface/AIInterface.h"
#include "AI/Controller/PNAIControllerBoss.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_FocusOnTarget::UBTService_FocusOnTarget()
{
	NodeName = TEXT("Focus On Target");
	Interval = 1.f;
}

void UBTService_FocusOnTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();
	IAIInterface* Interface = Cast<IAIInterface>(Owner);

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	Interface->GetAIController()->SetFocus(Target);
}
