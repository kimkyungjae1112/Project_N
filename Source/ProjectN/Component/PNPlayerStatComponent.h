// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PNPlayerStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChanged, float /* Current Hp */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnergyChanged, float /* Current Energy */);
DECLARE_MULTICAST_DELEGATE(FOnHpZero);

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

	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetHp() const { return Hp; }
	FORCEINLINE float GetMaxEnergy() const { return MaxEnergy; }
	FORCEINLINE float GetEnergy() const { return Energy; }
		
public:
	void ApplyDamage(float InDamage);
	void UseEnergy(float InEnergy);

private:
	void SetHp(float NewHp);

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxHp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float Hp;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float MaxEnergy;

	UPROPERTY(EditAnywhere, Category = "Stat")
	float Energy;

};
