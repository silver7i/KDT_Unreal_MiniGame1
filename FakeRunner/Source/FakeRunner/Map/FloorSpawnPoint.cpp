// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSpawnPoint.h"
#include "FadeFloor.h"

AFloorSpawnPoint::AFloorSpawnPoint()
{
	mTrigger->SetCollisionProfileName(TEXT("PlayerTrigger"));

	mTrigger->InitBoxExtent(FVector(130.f, 130.f, 130.f));

	mSpawnObject = nullptr;
}

void AFloorSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	mTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorSpawnPoint::BeginOverlap);

	Spawn();
}

void AFloorSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!mSpawnObject)
	{
		mAccTime += DeltaTime;
		if (mAccTime > mSpawnTime)
		{
			Spawn();
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Spawn"));
		}
	}
}

void AFloorSpawnPoint::Spawn()
{
	if (!IsValid(mSpawnClass))
		return;

	FActorSpawnParameters	SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	mSpawnObject = GetWorld()->SpawnActor<AFadeFloor>(mSpawnClass, GetActorLocation(), GetActorRotation(), SpawnParam);

	mSpawnObject->SetSpawnPoint(this);
}

void AFloorSpawnPoint::ClearSpawnObject()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("ClearSpawnObject"));

	mSpawnObject = nullptr;
	mAccTime = 0.f;
}

void AFloorSpawnPoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Hit"));

	mSpawnObject->DeleteFloor();
}
