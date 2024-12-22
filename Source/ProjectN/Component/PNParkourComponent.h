// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PNParkourComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTN_API UPNParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPNParkourComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Run();
	void Walk();

	void Crouch();
	void UnCrouch();

	void BeginRoll();
	void EndRoll(class UAnimMontage* Target, bool IsProperlyEnded);
	void RollMotionWarpSet();

/* 캐릭터 */
private:
	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class ACharacter> Character;

	UPROPERTY(VisibleAnywhere, Category = "Character")
	TObjectPtr<class UAnimInstance> Anim;

	UPROPERTY(VisibleAnywhere, Category = "Stat")
	TObjectPtr<class UPNPlayerStatComponent> StatComp;


/* 몽타주 */
private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> RollMontage;

	bool bRollCooldown = false;
};
