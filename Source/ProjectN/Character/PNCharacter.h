// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PNCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/HUDInterface.h"
#include "Interface/WeaponSocketCarryInterface.h"
#include "Interface/PlayerApplyDamageInterface.h"
#include "PNCharacter.generated.h"

DECLARE_DELEGATE(FChangeBehaviorState)

UENUM(BlueprintType)
enum class EBehaviorState : uint8
{
	EWalk = 0,
	ERun,
	ECrouch,
	EJump,
	ENonCombat
};

USTRUCT()
struct FChangeBehaviorStateWarpper //상태 변화
{
	GENERATED_BODY()

	FChangeBehaviorStateWarpper() {}
	FChangeBehaviorStateWarpper(const FChangeBehaviorState& ChagneBehaviorState) : ChangeBehaviorState(ChagneBehaviorState) { }

	FChangeBehaviorState ChangeBehaviorState;
};
/**
 * 
 */
UCLASS()
class PROJECTN_API APNCharacter : public APNCharacterBase, public IHUDInterface, public IWeaponSocketCarryInterface, public IPlayerApplyDamageInterface
{
	GENERATED_BODY()
	
public:
	APNCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	FORCEINLINE bool GetIsCharge() { return IsCharge; }
	FORCEINLINE void SetAfterAttack(bool Flag) { bAfterAttack = Flag; }
	FORCEINLINE USkeletalMeshComponent* GetWeapon() { return SwordMeshComp; }

public:
	class APNPlayerController* GetMyController();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/* IWeaponSocketCarryInterface */
	virtual class USkeletalMeshComponent* GetWeaponMeshComponent() override;

	/* IPlayerApplyDamageInterface -> 특정 공격을 받았을 때 */
	virtual void HitReaction() override;

/* Camera */
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> CameraComp;

/* Change Behavior State */
private:
	UPROPERTY(VisibleAnywhere, Category = "State")
	TMap<EBehaviorState, FChangeBehaviorStateWarpper> ChangeBehaviorStateMap;

	void SetBehaviorState(const EBehaviorState& BehaviorState);
	void SetBehaviorStateWalk();
	void SetBehaviorStateRun();
	void SetBehaviorStateCrouch();
	void SetBehaviorStateJump();
	void SetBehaviorStateNonCombat();

	void SetDead();
	void SetStun();

/* Input System */
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PNJump();
	void PNStopJump();
	void MouseLeftAttack();
	void MouseLeftAttackRelease();
	void MouseLeftChargeAttack();
	void MouseRightAttack();
	float PressTime = 0.f;
	bool IsCharge = false;
	bool bAfterAttack = false;

	void Run();
	void Walk();
	void OnCrouch();
	void UnnCrouch();
	void Roll();
	void DashAttack();
	void Assassination();
	void OnBlock();
	void UnBlock();
	bool bIsBlock = false;

	void ChangeNonCombat();
	bool HaveWeapon = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Utility", meta = (AllowPrivateAccess = "true"))
	EBehaviorState CurrentBehaviorState;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TMap<EBehaviorState, class UInputMappingContext*> IMC;

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

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> RunAndWalkAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;
	
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> CrouchAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> RollAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> DashAttackAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> AssassinationAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> BlockAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> WeaponSwapAction;

/* Mesh */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class USkeletalMeshComponent> SwordMeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class USkeletalMeshComponent> SheathMeshComp;

/* Components */
	UPROPERTY(VisibleAnywhere, Category = "Battle System")
	TObjectPtr<class UPNBattleSystemComponent> BattleSystemComp;

	UPROPERTY(VisibleAnywhere, Category = "Parkour System")
	TObjectPtr<class UPNParkourComponent> ParkourComp;

	UPROPERTY(VisibleAnywhere, Category = "Motion Warp")
	TObjectPtr<class UMotionWarpingComponent> MotionWarpComp;

	UPROPERTY(VisibleAnywhere, Category = "Stat System")
	TObjectPtr<class UPNPlayerStatComponent> StatComp;

/* UI */
	virtual void SetupHUD_Widget(class UPlayerHUDWidget* InHUDWidget) override;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<class UPlayerHUDWidget> HUDWidget;

	UPROPERTY(EditAnywhere, Category = "Montage")
	TObjectPtr<class UAnimMontage> DeadMontage;

};
