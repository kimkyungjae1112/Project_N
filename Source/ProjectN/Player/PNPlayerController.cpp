// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PNPlayerController.h"
#include "UI/PlayerHUDWidget.h"

APNPlayerController::APNPlayerController()
{
	static ConstructorHelpers::FClassFinder<UPlayerHUDWidget> HUDWidgetClassRef(TEXT("/Game/Project_N/UI/WBP_HUD.WBP_HUD_C"));
	if (HUDWidgetClassRef.Class)
	{
		HUDWidgetClass = HUDWidgetClassRef.Class;
	}
}

void APNPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APNPlayerController::RestartLevel, 5.f, false);
}

void APNPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	UPlayerHUDWidget* HUDWidget = CreateWidget<UPlayerHUDWidget>(this, HUDWidgetClass);
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}

}
