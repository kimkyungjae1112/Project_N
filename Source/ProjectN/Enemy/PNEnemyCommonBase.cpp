// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyCommonBase.h"
#include "UI/EnemyRefWidgetComponent.h"
#include "UI/EnemyHpBarWidget.h"

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

}

void APNEnemyCommonBase::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	Super::ApplyDamage(DamageAmount, DamageCauser, DamageType, ImpactLocation);


}

void APNEnemyCommonBase::SetHpBar(UEnemyHpBarWidget* InHpBar)
{
	InHpBar->SetMaxHp(1.f);
	InHpBar->UpdateHpBar(1.f);
}
