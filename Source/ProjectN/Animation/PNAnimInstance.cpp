// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PNAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UPNAnimInstance::UPNAnimInstance()
{
	MovingThreshould = 3.f;
	JumpingThreshould = 30.f;
	bIsBlock = false;
	bIsCrouch = false;
	bIsNoWeapon = false;
	bIsDetectPlayer = false;
}

void UPNAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(GetOwningActor());
	if (Character)
	{
		Movement = Character->GetCharacterMovement();
	}
}

void UPNAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size();
		Angle = UKismetMathLibrary::InverseTransformDirection(Character->GetActorTransform(), Velocity);
		bIsIdle = MovingThreshould > GroundSpeed;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}
}
