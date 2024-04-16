// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSpawnPoint.h"
#include "FadeFloor.h"

AFloorSpawnPoint::AFloorSpawnPoint()
{
	mTrigger->SetCollisionProfileName(TEXT("PlayerTrigger"));

	mTrigger->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	mTrigger->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));

	mSpawnObject = nullptr;
}

void AFloorSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	mTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorSpawnPoint::BeginOverlap);

	mScale3D = mTrigger->GetRelativeScale3D();
	Spawn();
}

void AFloorSpawnPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("AFloorSpawnPoint OnConstruction"));

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

	mSpawnObject->mSetSpawnPoint(this);
	mSpawnObject->mSetScale3D(mScale3D);
	mSpawnObject->mSetMaterial(mMaterial);
}

void AFloorSpawnPoint::ClearSpawnObject()
{
	mSpawnObject = nullptr;
	mAccTime = 0.f;
}

void AFloorSpawnPoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Hit"));

	if(mSpawnObject != nullptr)
		mSpawnObject->DeleteFloor(mDeleteDuration);
}
