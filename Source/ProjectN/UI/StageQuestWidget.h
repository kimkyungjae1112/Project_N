// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageQuestWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UStageQuestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UStageQuestWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

private:
	void CountEnemy();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UTextBlock> CountDeadEnemyText;

};
