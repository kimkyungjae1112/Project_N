// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PNPlayerStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float /* Current Hp */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnergyChanged, float /* Current Energy */);
DECLARE_MULTICAST_DELEGATE(FOnHpZero);
DECLARE_MULTICAST_DELEGATE(FOnEnergyZero);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTN_API UPNPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPNPlayerStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FOnHpChanged OnHpChanged;
	FOnEnergyChanged OnEnergyChanged;
	FOnHpZero OnHpZero;
	FOnEnergyZero OnEnergyZero;

	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetHp() const { return Hp; }
	FORCEINLINE float GetMaxEnergy() const { return MaxEnergy; }
	FORCEINLINE float GetEnergy() const { return Energy; }
	FORCEINLINE void SetEnergyFlag() { bEnergyFlag = true; }

	FORCEINLINE float UseLightAttackEnergy() const { return 7.f; }
	FORCEINLINE float UseHeavyAttackEnergy() const { return 12.f; }
	FORCEINLINE float UseDashAttackEnergy() const { return 10.f; }
	
		
public:
	void ApplyDamage(float InDamage);
	void ApplyEnergy(float InEnergy);

private:
	void SetHp(float NewHp);
	void SetEnergy(float InEnergy);

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxHp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float Hp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxEnergy;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float Energy;

	bool bEnergyFlag = true;
};
