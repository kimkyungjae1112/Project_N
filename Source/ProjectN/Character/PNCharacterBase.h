// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PNCharacterBase.generated.h"

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	BSCombat,
	BSNonCombat
};

UCLASS()
class PROJECTN_API APNCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APNCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

};
