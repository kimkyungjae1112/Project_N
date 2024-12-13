// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PNActiveBoss.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/PNEnemyBoss.h"
#include "Gimmick/PNThrone.h"

APNActiveBoss::APNActiveBoss()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComp;
	BoxComp->SetCollisionProfileName(TEXT("BossTrigger"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APNActiveBoss::OnComponentOverlap);
}

void APNActiveBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

void APNActiveBoss::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APNThrone* Throne = Cast<APNThrone>(UGameplayStatics::GetActorOfClass(GetWorld(), APNThrone::StaticClass()));
	if (Throne)
	{
		Throne->ActiveMoveThrone();
	}

	APNEnemyBoss* BossPtr = Cast<APNEnemyBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APNEnemyBoss::StaticClass()));
	if (BossPtr)
	{
		BossPtr->DisplayStatus();
	}
}


