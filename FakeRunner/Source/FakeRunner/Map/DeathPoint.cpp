// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathPoint.h"
#include "Player/PlayerCharacter.h"

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

	mTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADeathPoint::BeginOverlap);
	
}

// Called every frame
void ADeathPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathPoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	PlayerCharacter->SetPlayerStartLocation();
}

