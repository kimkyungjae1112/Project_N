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


	DefaultAttackCombo = 0;
}

float APNEnemyRampage::GetMeleeAttackInRange()
{
	Super::GetMeleeAttackInRange();

	return 300.f;
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

void APNEnemyRampage::NextComboAttack()
{
	Super::NextComboAttack();

	DefaultAttackCombo = FMath::Clamp(DefaultAttackCombo + 1, 0, 3);
	UE_LOG(LogTemp, Display, TEXT("DefaultAttackCombo %d"), DefaultAttackCombo);

	FName NextSection = *FString::Printf(TEXT("%s%d"), TEXT("Combo"), DefaultAttackCombo);
	UE_LOG(LogTemp, Display, TEXT("%s"), *NextSection.ToString());
	//왜 Combo3 은 실행이 안되냐?
	Anim->Montage_JumpToSection(NextSection, DefaultAttackMontage);
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
	UE_LOG(LogTemp, Display, TEXT("Attack 실행"));
	DefaultAttackCombo = 1;
	Anim->Montage_Play(DefaultAttackMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyRampage::EndDefaultAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, DefaultAttackMontage);
}

void APNEnemyRampage::EndDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	DefaultAttackCombo = 0;
	OnAttack_1_Finished.ExecuteIfBound();
}
