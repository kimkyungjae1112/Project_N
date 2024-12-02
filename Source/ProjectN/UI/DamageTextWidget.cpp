// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DamageTextWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"

UDamageTextWidget::UDamageTextWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DamagedTextEndDelegate.BindDynamic(this, &UDamageTextWidget::AnimationFinished);
}

void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));
	ensure(TextBlock);
	SetVisibility(ESlateVisibility::Hidden);

	BindToAnimationFinished(FadeOut, DamagedTextEndDelegate);
}

void UDamageTextWidget::SetDamageText(const FString& Damage)
{
	SetVisibility(ESlateVisibility::Visible);

	TextBlock->SetText(FText::FromString(Damage));

	if (FadeOut)
	{
		PlayAnimation(FadeOut);
	}
}

void UDamageTextWidget::AnimationFinished()
{
}
