// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PNCharacterBase.h"
#include "InputActionValue.h"
#include "PNCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API APNCharacter : public APNCharacterBase
{
	GENERATED_BODY()
	
public:
	APNCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	FORCEINLINE bool GetIsCharge() { return IsCharge; }

public:
	class APNPlayerController* GetMyController();

/* Camera */
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> CameraComp;

/* Input System */
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void MouseLeftAttack();
	void MouseLeftAttackRelease();
	void MouseLeftChargeAttack();
	void MouseRightAttack();

	float PressTime = 0.f;
	bool IsCharge = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Utility", meta = (AllowPrivateAccess = "true"))
	EBattleState CurrentBattleState;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> IMC_Comp;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MouseLeftChargeAttackAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MouseRightHeavyAttackAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MouseLeftAttackAction;

/* Mesh */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class USkeletalMeshComponent> SwordMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class USkeletalMeshComponent> SheathMeshComp;

/* Battle System Component */
	UPROPERTY(VisibleAnywhere, Category = "Battle System")
	TObjectPtr<class UPNBattleSystemComponent> BSComp;

};
