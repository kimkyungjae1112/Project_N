// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyRefWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UEnemyRefWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEnemyRefWidget(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE void SetOwningActor(AActor* Owner) { OwningActor = Owner; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	TObjectPtr<AActor> OwningActor;
};
