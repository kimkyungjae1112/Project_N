// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyCommonBase.h"
#include "UI/EnemyRefWidgetComponent.h"
#include "UI/EnemyHpBarWidget.h"
#include "UI/DamageTextWidget.h"
#include "NiagaraComponent.h"

FOnEnemyDead APNEnemyCommonBase::OnEnemyDead;

APNEnemyCommonBase::APNEnemyCommonBase()
{
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
}

void APNEnemyCommonBase::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	Super::ApplyDamage(DamageAmount, DamageCauser, DamageType, ImpactLocation);

	DisplayDamageTextUI(DamageAmount);

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
}

void APNEnemyCommonBase::DisplayDamageTextUI(float Damage)
{
	UDamageTextWidget* DamageText = Cast<UDamageTextWidget>(DamageTextWidgetComponent->GetWidget());
	if (DamageText)
	{
		DamageText->SetDamageText(FString::Printf(TEXT("%.0f"), Damage));
	}
}
