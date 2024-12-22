// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyCommonBase.h"
#include "UI/EnemyRefWidgetComponent.h"
#include "UI/EnemyHpBarWidget.h"
#include "UI/DamageTextWidget.h"
#include "NiagaraComponent.h"
#include "Perception/AISense_Damage.h"
#include "Components/SphereComponent.h"
#include "Engine/OverlapResult.h"

FOnEnemyDead APNEnemyCommonBase::OnEnemyDead;

APNEnemyCommonBase::APNEnemyCommonBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HpBarWidgetComponent = CreateDefaultSubobject<UEnemyRefWidgetComponent>(TEXT("HpBarWidgetComponent"));
	HpBarWidgetComponent->SetupAttachment(GetMesh());
	HpBarWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	static ConstructorHelpers::FClassFinder<UEnemyRefWidget> HpBarWidgetRef(TEXT("/Game/Project_N/UI/WBP_EnemyCommonHpBar.WBP_EnemyCommonHpBar_C"));
	if (HpBarWidgetRef.Class)
	{
		HpBarClass = HpBarWidgetRef.Class;
		HpBarWidgetComponent->SetWidgetClass(HpBarClass);
		HpBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarWidgetComponent->SetDrawSize(FVector2D(150.f, 15.f));
		HpBarWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	DamageTextWidgetComponent = CreateDefaultSubobject<UEnemyRefWidgetComponent>(TEXT("DamageTextWidgetComponent"));
	DamageTextWidgetComponent->SetupAttachment(GetMesh());
	DamageTextWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
	static ConstructorHelpers::FClassFinder<UDamageTextWidget> DamagedTextClassRef(TEXT("/Game/Project_N/UI/WBP_DamageText.WBP_DamageText_C"));
	if (DamagedTextClassRef.Class)
	{
		DamagedTextClass = DamagedTextClassRef.Class;
		DamageTextWidgetComponent->SetWidgetClass(DamagedTextClass);
		DamageTextWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		DamageTextWidgetComponent->SetDrawSize(FVector2D(5.f, 5.f));
		DamageTextWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	ImpactNiagaraComop = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Impact Niagara Component"));
	ImpactNiagaraComop->SetupAttachment(GetMesh());

	FirstDetectSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	FirstDetectSphereComp->SetupAttachment(GetMesh());
	FirstDetectSphereComp->SetCollisionProfileName(TEXT("ActiveTrigger"));

}

void APNEnemyCommonBase::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	Super::ApplyDamage(DamageAmount, DamageCauser, DamageType, ImpactLocation);

	DisplayDamageTextUI(DamageAmount);

	/* 대미지 입으면 감각 활성화 */
	UAISense_Damage::ReportDamageEvent(
		GetWorld(),
		this,
		DamageCauser,
		DamageAmount,
		GetActorLocation(),
		(GetActorLocation() - DamageCauser->GetActorLocation()).GetSafeNormal()
	);

	ImpactNiagaraComop->SetActive(true);
}

void APNEnemyCommonBase::NextComboAttack()
{
}

void APNEnemyCommonBase::SetHpBar(UEnemyHpBarWidget* InHpBar)
{
	if (InHpBar)
	{
		InHpBar->SetMaxHp(StatComp->GetMaxHp());
		InHpBar->UpdateHpBar(StatComp->GetHp());
		StatComp->OnHpChanged.AddUObject(InHpBar, &UEnemyHpBarWidget::UpdateHpBar);
	}
}

void APNEnemyCommonBase::SetDead()
{
	OnEnemyDead.ExecuteIfBound();

	FTimerHandle Temp;
	GetWorld()->GetTimerManager().SetTimer(Temp, [&]()
		{
			Destroy();
		}, 7.f, false);
}

void APNEnemyCommonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Origin = GetActorLocation();
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool bHit = GetWorld()->OverlapMultiByChannel(OverlapResults, Origin, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(800.f), Params);
	if (bHit)
	{
		HpBarWidgetComponent->SetVisibility(true);
	}
	else
	{
		HpBarWidgetComponent->SetVisibility(false);
	}
}

void APNEnemyCommonBase::DisplayDamageTextUI(float Damage)
{
	UDamageTextWidget* DamageText = Cast<UDamageTextWidget>(DamageTextWidgetComponent->GetWidget());
	if (DamageText)
	{
		DamageText->SetDamageText(FString::Printf(TEXT("%.0f"), Damage));
	}
}
