// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyRampage.h"
#include "AI/Controller/PNAIControllerRampage.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

APNEnemyRampage::APNEnemyRampage()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Meshes/Rampage.Rampage'"));
	if (BodyMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMeshRef.Object);
	}
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCharacterMovement()->MaxWalkSpeed = 500.f;


	DefaultAttackRange = 300.f;
}

float APNEnemyRampage::GetMeleeAttackInRange()
{
	Super::GetMeleeAttackInRange();

	return DefaultAttackRange;
}

void APNEnemyRampage::Attack_1()
{
	Super::Attack_1();

	BeginDefaultAttack();
}

void APNEnemyRampage::Attack_2()
{
	Super::Attack_2();

}

APNAIControllerBase* APNEnemyRampage::GetAIController()
{
	return GetMyController();
}

void APNEnemyRampage::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	Super::ApplyDamage(DamageAmount, DamageCauser, DamageType, ImpactLocation);

	StatComp->ApplyDamage(DamageAmount);
}

void APNEnemyRampage::BeginPlay()
{
	Super::BeginPlay();

	Anim = GetMesh()->GetAnimInstance();
}

APNAIControllerRampage* APNEnemyRampage::GetMyController()
{
	return CastChecked<APNAIControllerRampage>(GetController());
}

void APNEnemyRampage::BeginDefaultAttack()
{
	Anim->Montage_Play(DefaultAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyRampage::EndDefaultAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, DefaultAttackMontage);
}

void APNEnemyRampage::EndDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_1_Finished.ExecuteIfBound();
}
