// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathPoint.h"

// Sets default values
ADeathPoint::ADeathPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	SetRootComponent(mRoot);
	mTrigger->SetupAttachment(mRoot);

	mTrigger->SetCollisionProfileName(TEXT("PlayerTrigger"));

	mRoot->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void ADeathPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

