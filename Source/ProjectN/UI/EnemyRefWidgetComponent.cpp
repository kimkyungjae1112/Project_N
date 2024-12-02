// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyRefWidgetComponent.h"
#include "UI/EnemyRefWidget.h"

void UEnemyRefWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UEnemyRefWidget* UserWidget = Cast<UEnemyRefWidget>(GetWidget());
	if (UserWidget)
	{
		UserWidget->SetOwningActor(GetOwner());
	}
}
