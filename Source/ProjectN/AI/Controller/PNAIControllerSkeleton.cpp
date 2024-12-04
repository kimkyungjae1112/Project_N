// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/PNAIControllerSkeleton.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

APNAIControllerSkeleton::APNAIControllerSkeleton()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/Project_N/AI/Skeleton/BB_Skeleton.BB_Skeleton'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_N/AI/Skeleton/BT_Skeleton.BT_Skeleton'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}
}
