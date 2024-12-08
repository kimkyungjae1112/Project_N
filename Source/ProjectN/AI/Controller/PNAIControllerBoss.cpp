// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controller/PNAIControllerBoss.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/PNCharacter.h"
#include "Kismet/GameplayStatics.h"

APNAIControllerBoss::APNAIControllerBoss()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/Project_N/AI/Boss/BB_Boss.BB_Boss'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/Project_N/AI/Boss/BT_Boss.BT_Boss'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}
}

void APNAIControllerBoss::BeginPlay()
{
	Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), UGameplayStatics::GetActorOfClass(GetWorld(), APNCharacter::StaticClass()));
}

void APNAIControllerBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* Target = Cast<APawn>(GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target)
	{
		FRotator TargetRotation = (Target->GetActorLocation() - GetPawn()->GetActorLocation()).Rotation();
		TargetRotation.Roll = 0;
		TargetRotation.Pitch = 0;

		Interval += DeltaTime;
		if (Interval >= 2.5f)
		{
			FVector TargetLocation = Target->GetActorLocation();
			TargetLocation.X += FMath::RandRange(-1000.f, 1000.f);
			TargetLocation.Y += FMath::RandRange(-1000.f, 1000.f);
			MoveToLocation(TargetLocation);
			Interval = 0.f;
		}
		GetPawn()->SetActorRotation(TargetRotation);
	}
}

