// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PNAIControllerBase.generated.h"

UENUM()
enum class EAIPerceptionSense : uint8
{
	EPS_None = 0,
	EPS_Sight,
	EPS_Damage
};
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAIPerceptionComponent> AIPerception;
};
