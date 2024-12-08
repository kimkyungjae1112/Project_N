// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/PNEnemyTest.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"

APNEnemyTest::APNEnemyTest()
{
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle Component"));
	NiagaraComp->SetupAttachment(GetMesh());

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

}

void APNEnemyTest::ApplyDamage(float DamageAmount, AActor* DamageCauser, const FName& DamageType, const FVector& ImpactLocation)
{
	Super::ApplyDamage(DamageAmount, DamageCauser, DamageType, ImpactLocation);

	//NiagaraComp->SetRelativeLocation(ImpactLocation);
	NiagaraComp->Activate();

	StatComp->ApplyDamage(DamageAmount);
}
