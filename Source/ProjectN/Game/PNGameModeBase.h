// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PNGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APNGameModeBase();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> BGMComp;

	UPROPERTY(VisibleAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> BGMAsset;
};
