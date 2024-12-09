// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AI/Controller/PNAIControllerBoss.h"
#include "MotionWarpingComponent.h"
#include "Component/PNEnemyStatComponent.h"
#include "UI/BossStatusWidget.h"
#include "Engine/DamageEvents.h"

APNEnemyBoss::APNEnemyBoss()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DF_DRAGON_KNIGHT/MESHES/UE5/SK_Dragon_knight_UE5.SK_Dragon_knight_UE5'"));
	if (MeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	SwordMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sword Mesh Component"));
	SwordMeshComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DF_DRAGON_KNIGHT/MESHES/SWORD/SK_Dragon_knight_sword.SK_Dragon_knight_sword'"));
	if (SwordMeshRef.Object)
	{
		SwordMeshComp->SetSkeletalMesh(SwordMeshRef.Object);
	}

	MotionWarpComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("Motion Warping Component"));
	StatComp->OnHpZero.AddUObject(this, &APNEnemyBoss::SetDead);

	static ConstructorHelpers::FClassFinder<UBossStatusWidget> BossStatusClassRef(TEXT("/Game/Project_N/UI/WBP_BossStatus.WBP_BossStatus_C"));
	if (BossStatusClassRef.Class)
	{
		BossStatusClass = BossStatusClassRef.Class;
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
	return 400.0f;
}

void APNEnemyBoss::Attack_1()
{
	Super::Attack_1();

	BeginMeleeAttack_1();
}

void APNEnemyBoss::Attack_2()
{
	Super::Attack_2();

	BeginMeleeAttack_2();
}

void APNEnemyBoss::Attack_3()
{
	Super::Attack_3();

	BeginMeleeAttack_3();
}

void APNEnemyBoss::Attack_4()
{
	Super::Attack_4();

	BeginMeleeAttack_4();
}

void APNEnemyBoss::Attack_5()
{
	Super::Attack_5();

	BeginRangedAttack_1();
}

void APNEnemyBoss::Attack_6()
{
	Super::Attack_6();

	BeginRangedAttack_2();
}

APNAIControllerBase* APNEnemyBoss::GetAIController()
{
	return GetMyController();
}

void APNEnemyBoss::NextComboAttack()
{
	Super::NextComboAttack();

	Attack_1_Combo = FMath::Clamp(Attack_1_Combo + 1, 0, 3);
	UE_LOG(LogTemp, Display, TEXT("DefaultAttackCombo %d"), Attack_1_Combo);

	FName NextSection = *FString::Printf(TEXT("%s%d"), TEXT("Combo"), Attack_1_Combo);
	Anim->Montage_JumpToSection(NextSection, MeleeAttack_1_Montage);
}

void APNEnemyBoss::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	Super::ApplyDamage(DamageAmount, DamageCauser, DamageType, ImpactLocation);

	StatComp->ApplyDamage(DamageAmount);
}

void APNEnemyBoss::SetDead()
{
	Super::SetDead();

	GetMyController()->StopAI();
	Anim->Montage_Play(DeadMontage);
	SetActorEnableCollision(false);
}

USkeletalMeshComponent* APNEnemyBoss::GetWeaponMeshComponent()
{
	return SwordMeshComp;
}

uint8 APNEnemyBoss::GetCurrentCombo()
{
	return Attack_1_Combo;
}

void APNEnemyBoss::DisplayStatus()
{
	BossStatusPtr = CreateWidget<UBossStatusWidget>(GetWorld(), BossStatusClass);
	if (BossStatusPtr)
	{
		BossStatusPtr->AddToViewport();

		BossStatusPtr->SetMaxHp(StatComp->GetMaxHp());
		BossStatusPtr->UpdateHpBar(StatComp->GetMaxHp());
		StatComp->OnHpChanged.AddUObject(BossStatusPtr, &UBossStatusWidget::UpdateHpBar);
		
	}

}

void APNEnemyBoss::BeginMeleeAttack_1()
{
	Attack_1_Combo = 1;
	Anim->Montage_Play(MeleeAttack_1_Montage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndMeleeAttack_1);
	Anim->Montage_SetEndDelegate(MontageEnd, MeleeAttack_1_Montage);
}

void APNEnemyBoss::EndMeleeAttack_1(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_1_Finished.ExecuteIfBound();
}

void APNEnemyBoss::BeginMeleeAttack_2()
{
	Anim->Montage_Play(MeleeAttack_2_Montage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndMeleeAttack_2);
	Anim->Montage_SetEndDelegate(MontageEnd, MeleeAttack_2_Montage);
}

void APNEnemyBoss::EndMeleeAttack_2(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_2_Finished.ExecuteIfBound();
}

void APNEnemyBoss::BeginMeleeAttack_3()
{
	Anim->Montage_Play(MeleeAttack_3_Montage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndMeleeAttack_3);
	Anim->Montage_SetEndDelegate(MontageEnd, MeleeAttack_3_Montage);
}

void APNEnemyBoss::EndMeleeAttack_3(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_3_Finished.ExecuteIfBound();
}

void APNEnemyBoss::Attack_3_HitCheck()
{
	FVector Origin = GetActorLocation() + FVector(100.f, 0.f, 50.f);
	FVector End = Origin + GetActorForwardVector() * 100.f;
	FVector BoxExtent = FVector(100.f);
	
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Origin, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeBox(BoxExtent), Params);
	if (bHit)
	{
		// 넉백 효과를 넣고 싶은데
		AActor* Target = HitResult.GetActor();
		FDamageEvent DamageEvent;
		Target->TakeDamage(300.f, DamageEvent, GetMyController(), this);
	}
}

void APNEnemyBoss::BeginMeleeAttack_4()
{
	Attack_4_MotionWarpSet();
	Anim->Montage_Play(MeleeAttack_4_Montage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndMeleeAttack_4);
	Anim->Montage_SetEndDelegate(MontageEnd, MeleeAttack_4_Montage);
}

void APNEnemyBoss::EndMeleeAttack_4(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_4_Finished.ExecuteIfBound();
}

void APNEnemyBoss::Attack_4_MotionWarpSet()
{
	FVector Origin = GetActorLocation();
	FVector End = Origin + GetActorForwardVector() * 500.f;
	MotionWarpComp->AddOrUpdateWarpTargetFromLocation(TEXT("Attack4"), End);
}

void APNEnemyBoss::Attack_4_HitCheck()
{
	FVector Origin = GetActorLocation();
	FVector End = Origin - GetActorForwardVector() * 500.f;

	FVector BoxExtent = FVector(100.f);

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Origin, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeBox(BoxExtent), Params);
	if (bHit)
	{
		// 넉백 효과를 넣고 싶은데
		AActor* Target = HitResult.GetActor();
		FDamageEvent DamageEvent;
		Target->TakeDamage(300.f, DamageEvent, GetMyController(), this);
	}
}

void APNEnemyBoss::BeginRangedAttack_1()
{
	Anim->Montage_Play(RangedAttack_1_Montage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndRangedAttack_1);
	Anim->Montage_SetEndDelegate(MontageEnd, RangedAttack_1_Montage);
}

void APNEnemyBoss::EndRangedAttack_1(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_5_Finished.ExecuteIfBound();
}

void APNEnemyBoss::Attack_5_HitCheck()
{
}

void APNEnemyBoss::BeginRangedAttack_2()
{
	Anim->Montage_Play(RangedAttack_2_Montage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndRangedAttack_2);
	Anim->Montage_SetEndDelegate(MontageEnd, RangedAttack_2_Montage);
}

void APNEnemyBoss::EndRangedAttack_2(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_6_Finished.ExecuteIfBound();
}

void APNEnemyBoss::Attack_6_HitCheck()
{
}

APNAIControllerBoss* APNEnemyBoss::GetMyController()
{
	return CastChecked<APNAIControllerBoss>(GetController());
}
