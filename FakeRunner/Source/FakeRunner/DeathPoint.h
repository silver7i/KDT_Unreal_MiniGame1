// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "DeathPoint.generated.h"

UCLASS()
class FAKERUNNER_API ADeathPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathPoint();

protected:
	USceneComponent* mRoot;

	UPROPERTY(EditAnywhere)
	UBoxComponent* mTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
