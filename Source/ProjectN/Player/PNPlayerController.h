// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PNPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APNPlayerController();

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	TSubclassOf<class UPlayerHUDWidget> HUDWidgetClass;
	
};
