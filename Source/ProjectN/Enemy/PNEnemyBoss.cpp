// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyBoss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "AI/Controller/PNAIControllerBoss.h"
#include "MotionWarpingComponent.h"
#include "Component/PNEnemyStatComponent.h"
#include "UI/BossStatusWidget.h"
#include "Engine/DamageEvents.h"
#include "Interface/PlayerApplyDamageInterface.h"
#include "Projectile/BossProtectileRanged2.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/OverlapResult.h"

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

	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComp->SetupAttachment(SwordMeshComp);
	NiagaraComp->bAutoActivate = false;
	//NiagaraComp->SetRelativeScale3D(FVector(0.5f))

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

	GetMyController()->StopAI();

	Anim = GetMesh()->GetAnimInstance();
	ensure(Anim);
}

float APNEnemyBoss::GetMeleeAttackInRange()
{
	return 500.0f;
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

void APNEnemyBoss::StartMotion()
{
	BeginStartMotion();
}

void APNEnemyBoss::SetMoveFlag()
{
	GetMyController()->SetMoveFlag();
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
	NiagaraComp->SetActive(true);
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
	Attack_3_MotionWarpSet();
	Anim->Montage_Play(MeleeAttack_3_Montage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndMeleeAttack_3);
	Anim->Montage_SetEndDelegate(MontageEnd, MeleeAttack_3_Montage);
}

void APNEnemyBoss::EndMeleeAttack_3(UAnimMontage* Target, bool IsProperlyEnded)
{
	OnAttack_3_Finished.ExecuteIfBound();
}

void APNEnemyBoss::Attack_3_MotionWarpSet()
{
	FVector Origin = GetActorLocation();
	FVector End = Origin + GetActorForwardVector() * 250.f;
	MotionWarpComp->AddOrUpdateWarpTargetFromLocation(TEXT("Attack3"), End);
}

void APNEnemyBoss::Attack_3_HitCheck()
{
	FVector Origin = GetActorLocation() + FVector(100.f, 0.f, 50.f);
	FVector End = Origin + GetActorForwardVector() * 100.f;
	FVector BoxExtent = FVector(100.f);

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	//DrawDebugBox(GetWorld(), Origin, BoxExtent, FQuat::Identity, FColor::Red, false, 1.f);
	//DrawDebugBox(GetWorld(), End, BoxExtent, FQuat::Identity, FColor::Green, false, 1.f);

	//// 히트 경로를 선으로 디버깅
	//DrawDebugLine(GetWorld(), Origin, End, FColor::Blue, false, 1.f, 0, 2.f);

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Origin, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeBox(BoxExtent), Params);
	if (bHit)
	{
		// 넉백 효과를 넣고 싶은데
		AActor* Target = HitResult.GetActor();
		FDamageEvent DamageEvent;
		Target->TakeDamage(300.f, DamageEvent, GetMyController(), this);

		IPlayerApplyDamageInterface* Interface = Cast<IPlayerApplyDamageInterface>(Target);
		if (Interface)
		{
			Interface->HitReaction();
		}
	}
}

void APNEnemyBoss::BeginMeleeAttack_4()
{
	Attack_4_MotionWarpSet();
	Anim->Montage_Play(MeleeAttack_4_Montage);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Attack4"));

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndMeleeAttack_4);
	Anim->Montage_SetEndDelegate(MontageEnd, MeleeAttack_4_Montage);
}

void APNEnemyBoss::EndMeleeAttack_4(UAnimMontage* Target, bool IsProperlyEnded)
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));
	OnAttack_4_Finished.ExecuteIfBound();
}

void APNEnemyBoss::Attack_4_MotionWarpSet()
{
	FVector Origin = GetActorLocation();
	FVector End = Origin + GetActorForwardVector() * 1000.f;
	MotionWarpComp->AddOrUpdateWarpTargetFromLocation(TEXT("Attack4"), End);
}

void APNEnemyBoss::Attack_4_HitCheck()
{
	FVector Origin = GetActorLocation();
	FVector End = Origin - GetActorForwardVector() * 1000.f;

	FVector BoxExtent = FVector(100.f);

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	
	//DrawDebugBox(GetWorld(), Origin, BoxExtent, FQuat::Identity, FColor::Red, false, 1.f); // 시작 위치
	//DrawDebugBox(GetWorld(), End, BoxExtent, FQuat::Identity, FColor::Green, false, 1.f); // 끝 위치

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, Origin, End, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeBox(BoxExtent), Params);
	if (bHit)
	{
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
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Attack_5_Effect, GetActorLocation() + GetActorForwardVector() * 300.f - FVector(0.f, 0.f, 30.f));

	FVector Origin = GetActorLocation();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool bHit = GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(300.f), Params);
	if (bHit)
	{
		for (const FOverlapResult& HitResult : OverlapResults)
		{
			AActor* Target = HitResult.GetActor();
			FDamageEvent DamageEvent;
			Target->TakeDamage(500.f, DamageEvent, GetMyController(), this);
		}
	}
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
	ABossProtectileRanged2* Projectile = GetWorld()->SpawnActor<ABossProtectileRanged2>(RangedSkill_2_Class, GetActorLocation() + FVector(100.f, 0.f, 50.f), GetActorForwardVector().Rotation());
	if (Projectile)
	{
		Projectile->Init(GetActorForwardVector(), GetMyController());
	}
}

void APNEnemyBoss::BeginStartMotion()
{
	Anim->Montage_Play(StartMotionMontage);

	FOnMontageEnded MontageEnd;
	MontageEnd.BindUObject(this, &APNEnemyBoss::EndStartMotion);
	Anim->Montage_SetEndDelegate(MontageEnd, StartMotionMontage);
}

void APNEnemyBoss::EndStartMotion(UAnimMontage* Target, bool IsProperlyEnded)
{
	GetMyController()->RunAI();
	DisplayStatus();
}

APNAIControllerBoss* APNEnemyBoss::GetMyController()
{
	return CastChecked<APNAIControllerBoss>(GetController());
}
