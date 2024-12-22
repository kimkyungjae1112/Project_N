// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossProtectileRanged2.generated.h"

UCLASS()
class PROJECTN_API ABossProtectileRanged2 : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossProtectileRanged2();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	void Init(const FVector& InDirection, AController* InController);


private:
	UFUNCTION()
	void OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, Category = "Box")
	TObjectPtr<class UBoxComponent> BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Effect")
	TObjectPtr<class UNiagaraComponent> NiagaraComp;

	float LifeTime = 5.f;
	float Speed = 1500.f;
	FVector Direction = FVector::ZeroVector;
	AController* Controller;
};
