// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PNAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
public:
	APNAIControllerBase();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<class UBlackboardData> BBData;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<class UBehaviorTree> BTData;

};
