// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/PNAIControllerRampage.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

APNAIControllerRampage::APNAIControllerRampage()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/Project_N/AI/Rampage/BB_Rampage.BB_Rampage'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_N/AI/Rampage/BT_Rampage.BT_Rampage'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}
}
