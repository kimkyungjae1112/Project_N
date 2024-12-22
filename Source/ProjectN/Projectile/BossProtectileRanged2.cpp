// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BossProtectileRanged2.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Engine/DamageEvents.h"

ABossProtectileRanged2::ABossProtectileRanged2()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComp;
	BoxComp->SetCollisionProfileName(TEXT("ActiveStage"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABossProtectileRanged2::OnComponentOverlap);


	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComp->SetupAttachment(BoxComp);
}

void ABossProtectileRanged2::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossProtectileRanged2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (Direction * 1500.f * DeltaTime);
	SetActorLocation(NewLocation);

	LifeTime -= DeltaTime;
	if (LifeTime <= 0.f)
	{
		Destroy();
	}
}

void ABossProtectileRanged2::Init(const FVector& InDirection, AController* InController)
{
	Direction = InDirection;
	Controller = InController;
}

void ABossProtectileRanged2::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this && OtherActor->ActorHasTag(TEXT("Player")))
	{
		FDamageEvent DamageEvent;
		OtherActor->TakeDamage(300.f, DamageEvent, Controller, this);
	}
}

