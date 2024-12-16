// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/PNAIControllerBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Character/PNCharacter.h"
#include "Perception/AIPerceptionComponent.h"

APNAIControllerBase::APNAIControllerBase()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SetPerceptionComponent(*AIPerception);
}

void APNAIControllerBase::RunAI()
{
	UBlackboardComponent* BBComp = Blackboard.Get();
	if (UseBlackboard(BBData, BBComp))
	{
		bool RunResult = RunBehaviorTree(BTData);
	}
}

void APNAIControllerBase::StopAI()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp)
	{
		BTComp->StopTree();
	}
}

void APNAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
