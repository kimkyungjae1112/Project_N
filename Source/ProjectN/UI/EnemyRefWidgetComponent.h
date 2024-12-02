// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnemyRefWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UEnemyRefWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
};
