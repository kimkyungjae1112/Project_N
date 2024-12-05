// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/Controller/PNAIControllerBoss.h"

APNEnemyBoss::APNEnemyBoss()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DF_DRAGON_KNIGHT/MESHES/UE5/SK_Dragon_knight_UE5.SK_Dragon_knight_UE5'"));
	if (MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	SwordMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sword Mesh Component"));
	SwordMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DF_DRAGON_KNIGHT/MESHES/SWORD/SK_Dragon_knight_sword.SK_Dragon_knight_sword'"));
	if (SwordMeshRef.Object)
	{
		SwordMeshComp->SetSkeletalMesh(SwordMeshRef.Object);
	}

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void APNEnemyBoss::BeginPlay()
{
	Super::BeginPlay();

	Anim = GetMesh()->GetAnimInstance();
	ensure(Anim);
}

float APNEnemyBoss::GetMeleeAttackInRange()
{
	return 550.0f;
}

void APNEnemyBoss::Attack_1()
{
	Super::Attack_1();

	BeginAttack_1_Default();
}

void APNEnemyBoss::Attack_2()
{
	Super::Attack_2();

}

APNAIControllerBase* APNEnemyBoss::GetAIController()
{
	return GetMyController();
}

void APNEnemyBoss::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	Super::ApplyDamage(DamageAmount, DamageCauser, DamageType, ImpactLocation);

}

void APNEnemyBoss::SetDead()
{
}

void APNEnemyBoss::BeginAttack_1_Default()
{
	Anim->Montage_Play(Attack_1_Montage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndAttack_1_Default);
	Anim->Montage_SetEndDelegate(MontageEnd, Attack_1_Montage);
}

void APNEnemyBoss::EndAttack_1_Default(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_1_Finished.ExecuteIfBound();
}

APNAIControllerBoss* APNEnemyBoss::GetMyController()
{
	return CastChecked<APNAIControllerBoss>(GetController());
}
