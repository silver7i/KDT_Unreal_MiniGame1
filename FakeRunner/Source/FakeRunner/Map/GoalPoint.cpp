// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalPoint.h"

// Sets default values
AGoalPoint::AGoalPoint()
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
void AGoalPoint::BeginPlay()
{
	Super::BeginPlay();
	
	mTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGoalPoint::BeginOverlap);
}

// Called every frame
void AGoalPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalPoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("GoalPoint"));

	UGameplayStatics::OpenLevel(GetWorld(), mLevelName);
}

