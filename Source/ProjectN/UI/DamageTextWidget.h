// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTN_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UDamageTextWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void SetDamageText(const FString& Damage);

	UFUNCTION()
	void AnimationFinished();

	FWidgetAnimationDynamicEvent DamagedTextEndDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> FadeOut;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Text", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTextBlock> TextBlock;
};
