// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Controller/PNAIControllerBase.h"
#include "PNAIControllerSkeleton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNAIControllerSkeleton : public APNAIControllerBase
{
	GENERATED_BODY()
	
public:
	APNAIControllerSkeleton();

public:
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);


	/* Perception Sense 섹션 */
private:
	FAIStimulus CanSenseActor(AActor* Actor, EAIPerceptionSense AIPerceptionSense);

	void HandleSenseSight(AActor* Actor, const FAIStimulus& AIStimulus);
	void HandleSenseDamage(AActor* Actor, const FAIStimulus& AIStimulus);

private:
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;
	TObjectPtr<class UAISenseConfig_Damage> DamageConfig;
};
