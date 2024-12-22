// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PNActiveBoss.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/PNEnemyBoss.h"
#include "Gimmick/PNThrone.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "Game/GameManagerSubsystem.h"
#include "Player/PNPlayerController.h"

APNActiveBoss::APNActiveBoss()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComp;
	BoxComp->SetCollisionProfileName(TEXT("BossTrigger"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APNActiveBoss::OnComponentOverlap);

	static ConstructorHelpers::FObjectFinder<ULevelSequence> LevelSequenceAssetRef(TEXT("/Script/LevelSequence.LevelSequence'/Game/Project_N/Blueprints/Cinematic/BossIntro.BossIntro'"));
	if (LevelSequenceAssetRef.Object)
	{
		LevelSequenceAsset = LevelSequenceAssetRef.Object;
	}
}

void APNActiveBoss::BeginPlay()
{
	Super::BeginPlay();

	// 레벨 시퀀스를 재생할 준비
	ULevelSequence* Sequence = LevelSequenceAsset.Get();
	ALevelSequenceActor* SequenceActor;
	if (Sequence)
	{
		// 시퀀스 플레이어와 액터 생성
		FMovieSceneSequencePlaybackSettings PlaybackSettings;
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(),
			Sequence,
			PlaybackSettings,
			SequenceActor
		);
	}

	if (LevelSequencePlayer)
	{
		LevelSequencePlayer->OnFinished.AddDynamic(this, &APNActiveBoss::OnSequenceFinished);
	}

	GetGameInstance()->GetSubsystem<UGameManagerSubsystem>()->OnCompleteStageSign.AddUObject(this, &APNActiveBoss::ActiveStage);
}

void APNActiveBoss::OnComponentOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APNPlayerController* Controller = Cast<APNPlayerController>(GetWorld()->GetFirstPlayerController());
	if (Controller)
	{
		APawn* ControlledPawn = Controller->GetPawn();
		if (ControlledPawn)
		{
			ControlledPawn->DisableInput(Controller);
		}
	}

	APNThrone* Throne = Cast<APNThrone>(UGameplayStatics::GetActorOfClass(GetWorld(), APNThrone::StaticClass()));
	if (Throne)
	{
		Throne->ActiveMoveThrone();
	}

	APNEnemyBoss* BossPtr = Cast<APNEnemyBoss>(UGameplayStatics::GetActorOfClass(GetWorld(), APNEnemyBoss::StaticClass()));
	if (BossPtr)
	{
		FTimerHandle StartMotionTimer;
		GetWorld()->GetTimerManager().SetTimer(StartMotionTimer, BossPtr, &APNEnemyBoss::StartMotion, 10.f, false);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, BossPtr, &APNEnemyBoss::SetMoveFlag, 20.f, false);
	}

	LevelSequencePlayer->Play();
}

void APNActiveBoss::OnSequenceFinished()
{
	APNPlayerController* Controller = Cast<APNPlayerController>(GetWorld()->GetFirstPlayerController());
	if (Controller)
	{
		APawn* ControlledPawn = Controller->GetPawn();
		if (ControlledPawn)
		{
			ControlledPawn->EnableInput(Controller);
		}
	}

}

void APNActiveBoss::ActiveStage()
{
	BoxComp->SetCollisionProfileName(TEXT("ActiveTrigger"));
}


