// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PNActiveStage.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Game/GameManagerSubsystem.h"

APNActiveStage::APNActiveStage()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	RootComponent = BoxComp;
	BoxComp->SetCollisionProfileName(TEXT("ActiveTrigger"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APNActiveStage::OnComponentOverlap);

	static ConstructorHelpers::FClassFinder<UUserWidget> UIRef(TEXT("/Game/Project_N/UI/WBP_StageQuest.WBP_StageQuest_C"));
	if (UIRef.Class)
	{
		UIClass = UIRef.Class;
	}
}

void APNActiveStage::BeginPlay()
{
	Super::BeginPlay();
	
	GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->OnCompleteStageSign.AddUObject(this, &APNActiveStage::CompleteQuest);
}

void APNActiveStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APNActiveStage::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UIPtr = CreateWidget(GetWorld(), UIClass);
	if (UIPtr && !UIPtr->IsInViewport())
	{
		UIPtr->AddToViewport();
	}
}

void APNActiveStage::CompleteQuest()
{
	if (UIPtr->IsInViewport())
	{
		UIPtr->RemoveFromViewport();
	}
}

