// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PNParkourComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/PNAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "MotionWarpingComponent.h"
#include "Component/PNPlayerStatComponent.h"

UPNParkourComponent::UPNParkourComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPNParkourComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = CastChecked<ACharacter>(GetOwner());
	if (Character)
	{
		Anim = Character->GetMesh()->GetAnimInstance();
	}

	StatComp = GetOwner()->GetComponentByClass<UPNPlayerStatComponent>();
}


void UPNParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsRun)
	{
		StatComp->ApplyEnergy(1.f);
	}
}

void UPNParkourComponent::Run()
{
	Character->GetCharacterMovement()->MaxWalkSpeed = 600.f;
	bIsRun = true;
}

void UPNParkourComponent::Walk()
{
	Character->GetCharacterMovement()->MaxWalkSpeed = 300.f;
	bIsRun = false;
}

void UPNParkourComponent::Crouch()
{
	UPNAnimInstance* PNAnim = Cast<UPNAnimInstance>(Anim);
	
	PNAnim->bIsCrouch = true;
	Character->GetCharacterMovement()->MaxWalkSpeed = 250.f;
}

void UPNParkourComponent::UnCrouch()
{
	UPNAnimInstance* PNAnim = Cast<UPNAnimInstance>(Anim);

	PNAnim->bIsCrouch = false;
	Character->GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void UPNParkourComponent::BeginRoll()
{
	StatComp->ApplyEnergy(20.f);
	RollMotionWarpSet();
	Anim->Montage_Play(RollMontage);
	//Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &UPNParkourComponent::EndRoll);
	Anim->Montage_SetEndDelegate(MontageEnd, RollMontage);
}

void UPNParkourComponent::EndRoll(UAnimMontage* Target, bool IsProperlyEnded)
{
	//Character->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
}

void UPNParkourComponent::RollMotionWarpSet()
{
	UMotionWarpingComponent* MotionWarp = Character->GetComponentByClass<UMotionWarpingComponent>();
	if (MotionWarp)
	{
		FVector Origin = Character->GetActorLocation();
		FVector Target = Origin + Character->GetActorForwardVector() * 300.f;

		UE_LOG(LogTemp, Display, TEXT("MotionWarp Set?"));
		MotionWarp->AddOrUpdateWarpTargetFromLocation(TEXT("Roll"), Target);
	}
}

