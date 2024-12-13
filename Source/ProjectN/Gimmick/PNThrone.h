// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PNThrone.generated.h"

UCLASS()
class PROJECTN_API APNThrone : public AActor
{
	GENERATED_BODY()
	
public:	
	APNThrone();

	void ActiveMoveThrone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> MainBodyComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;

	FVector Origin;
	bool bActiveMove = false;
};
