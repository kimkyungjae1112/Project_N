// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemySkeleton.h"
#include "AI/Controller/PNAIControllerSkeleton.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

APNEnemySkeleton::APNEnemySkeleton()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BodyMesh_4_Ref(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_04/mesh/SK_SKnight_full_04.SK_SKnight_full_04'"));
	if (BodyMesh_4_Ref.Object)
	{
		GetMesh()->SetSkeletalMesh(BodyMesh_4_Ref.Object);
	}

	WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh Component"));
	WeaponMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh_3_Ref(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_05/mesh/weapon/SK_weapon_05.SK_weapon_05'"));
	if (WeaponMesh_3_Ref.Object)
	{
		WeaponMeshComp->SetSkeletalMesh (WeaponMesh_3_Ref.Object);
	}
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	DefaultAttackCombo = 0;
}

float APNEnemySkeleton::GetMeleeAttackInRange()
{
	if (WeaponType == EWeaponType::Spear)
	{
		return 600.f;
	}
	return 300.f;
}

void APNEnemySkeleton::Attack_1()
{
	Super::Attack_1();

	BeginDefaultAttack();
}

void APNEnemySkeleton::Attack_2()
{
	Super::Attack_2();

}

APNAIControllerBase* APNEnemySkeleton::GetAIController()
{
	return GetMyController();
}

void APNEnemySkeleton::NextComboAttack()
{
}

void APNEnemySkeleton::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	Super::ApplyDamage(DamageAmount, DamageCauser, DamageType, ImpactLocation);

	StatComp->ApplyDamage(DamageAmount);
}

void APNEnemySkeleton::SetDead()
{
	Super::SetDead();

	GetMyController()->StopAI();

	Anim->StopAllMontages(0.5f);
	Anim->Montage_Play(CurrentWeaponMontages[1]);

	SetActorEnableCollision(false);
}

USkeletalMeshComponent* APNEnemySkeleton::GetWeaponMeshComponent()
{
	return WeaponMeshComp;
}

void APNEnemySkeleton::BeginPlay()
{
	Super::BeginPlay();

	Anim = GetMesh()->GetAnimInstance();

	switch (WeaponType)
	{
	case EWeaponType::Sword:
		CurrentWeaponMontages = SwordMontages;
		break;
	case EWeaponType::Axe:
		CurrentWeaponMontages = AxeMontages;
		break;
	case EWeaponType::Spear:
		CurrentWeaponMontages = SpearMontages;
		break;
	}
}

APNAIControllerSkeleton* APNEnemySkeleton::GetMyController()
{
	return CastChecked<APNAIControllerSkeleton>(GetController());
}

void APNEnemySkeleton::BeginDefaultAttack()
{
	Anim->Montage_Play(CurrentWeaponMontages[0]);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemySkeleton::EndDefaultAttack);
	Anim->Montage_SetEndDelegate(MontageEnd, CurrentWeaponMontages[0]);
}

void APNEnemySkeleton::EndDefaultAttack(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_1_Finished.ExecuteIfBound();
}
