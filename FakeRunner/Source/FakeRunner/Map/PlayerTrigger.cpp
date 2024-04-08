// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/PlayerTrigger.h"

// Sets default values
APlayerTrigger::APlayerTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	SetRootComponent(mRoot);
	mTrigger->SetupAttachment(mRoot);

	mRoot->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void APlayerTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

