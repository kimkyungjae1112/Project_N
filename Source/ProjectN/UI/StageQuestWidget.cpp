// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StageQuestWidget.h"
#include "Components/TextBlock.h"
#include "Enemy/PNEnemyCommonBase.h"
#include "Game/GameManagerSubsystem.h"

UStageQuestWidget::UStageQuestWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStageQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CountDeadEnemyText = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_Amount")));
	ensure(CountDeadEnemyText);

	GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->OnEnemyDeadSign.BindUObject(this, &UStageQuestWidget::CountEnemy);
}

void UStageQuestWidget::CountEnemy()
{
	int32 Count = GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->GetDeadCountEnemyNum();
	CountDeadEnemyText->SetText(FText::FromString(*FString::Printf(TEXT("%d"), Count)));
}
