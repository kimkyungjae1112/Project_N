// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PNActiveBoss.generated.h"

UCLASS()
class PROJECTN_API APNActiveBoss : public AActor
{
	GENERATED_BODY()
	
public:	
	APNActiveBoss();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, Category = "Comp")
	TObjectPtr<class UBoxComponent> BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Sequnce")
	TSoftObjectPtr<class ULevelSequence> LevelSequenceAsset;

	UPROPERTY(EditAnywhere, Category = "Sequnce")
	TObjectPtr<class ULevelSequencePlayer> LevelSequencePlayer;
};
