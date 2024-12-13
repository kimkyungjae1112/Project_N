// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PNGameModeBase.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"

APNGameModeBase::APNGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/Project_N/Blueprints/Player/BP_PNCharacter.BP_PNCharacter_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/CoreUObject.Class'/Script/ProjectN.PNPlayerController'"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	BGMComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	BGMComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundWave> BGMAssetRef(TEXT("/Script/Engine.SoundWave'/Game/Project_N/Sound/bgm029-dark-fantasy-horror-mystery-horror-148349.bgm029-dark-fantasy-horror-mystery-horror-148349'"));
	if (BGMAssetRef.Object)
	{
		BGMAsset = BGMAssetRef.Object;
	}
}

void APNGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	BGMComp->SetSound(BGMAsset);
	BGMComp->Play();
}
