// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "PlayerTrigger.generated.h"

UCLASS()
class FAKERUNNER_API APlayerTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerTrigger();

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* mTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
