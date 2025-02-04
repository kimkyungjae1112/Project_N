// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PNEnemyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float /* Current Hp */);
DECLARE_MULTICAST_DELEGATE(FOnHpZero);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTN_API UPNEnemyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPNEnemyStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnHpChanged OnHpChanged;
	FOnHpZero OnHpZero;

	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetHp() const { return Hp; }

public:
	void ApplyDamage(float InDamage);

private:
	void SetHp(float NewHp);

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxHp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float Hp;
};
