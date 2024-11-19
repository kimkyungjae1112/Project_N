// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PNCharacterComboDataAsset.generated.h"

UENUM(BlueprintType)
enum class EAttackMontage : uint8
{
	Light,
	Heavy,
	Charge
};

USTRUCT(BlueprintType)
struct FEffectiveFrameData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComboData")
	TArray<float> FrameCounts;
};

/**
 *
 */
UCLASS()
class PROJECTN_API UPNCharacterComboDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Name")
	TMap<EAttackMontage, FString> SectionName;

	UPROPERTY(EditAnywhere, Category = "Combo")
	TMap<EAttackMontage, int32> MaxCombo;

	UPROPERTY(EditAnywhere, Category = "Frame")
	TMap<EAttackMontage, float> FrameRate;

	UPROPERTY(EditAnywhere, Category = "ComboData")
	TMap<EAttackMontage, FEffectiveFrameData> EffectiveFrameCount;

};
