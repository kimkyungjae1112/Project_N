// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PNThrone.h"
#include "Camera/CameraShakeBase.h"

APNThrone::APNThrone()
{
	PrimaryActorTick.bCanEverTick = true;

	MainBodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Body Component"));
	RootComponent = MainBodyComp;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MainBodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Dragon_Rise/Meshes/SM_Throne_02.SM_Throne_02'"));
	if (MainBodyMeshRef.Object)
	{
		MainBodyComp->SetStaticMesh(MainBodyMeshRef.Object);
	}
	
	static ConstructorHelpers::FClassFinder<UCameraShakeBase> CameraShakeClassRef(TEXT("/Game/Project_N/Blueprints/Gimmick/BP_CameraShake.BP_CameraShake_C"));
	if (CameraShakeClass = CameraShakeClassRef.Class)
	{
		CameraShakeClass = CameraShakeClassRef.Class;
	}
}

void APNThrone::ActiveMoveThrone()
{
	bActiveMove = true;
	FTimerHandle CameraShakeHandle;
	
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeClass);
	GetWorld()->GetTimerManager().SetTimer(CameraShakeHandle, [&]()
		{
			GetWorld()->GetFirstPlayerController()->ClientStopCameraShake(CameraShakeClass);
		}, 7.f, false);
}

void APNThrone::BeginPlay()
{
	Super::BeginPlay();

	Origin = GetActorLocation();
}

void APNThrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bActiveMove)
	{
		FVector Start = GetActorLocation();
		FVector End = Origin - FVector(0.f, 0.f, 5000.f);
		SetActorLocation(FMath::VInterpTo(Start, End, DeltaTime, 0.3f));
	}
}

