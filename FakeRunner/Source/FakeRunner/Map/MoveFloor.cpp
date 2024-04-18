// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveFloor.h"
#include "FadeFloor.h"


AMoveFloor::AMoveFloor()
{
	mTrigger->SetCollisionProfileName(TEXT("PlayerTrigger"));

	mTrigger->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	mTrigger->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));

	mSpawnObject = nullptr;
}

void AMoveFloor::BeginPlay()
{
	Super::BeginPlay();

}

void AMoveFloor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

void AMoveFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMoveFloor::Spawn()
{
	//if (!IsValid(mSpawnClass))
	//	return;

	//FActorSpawnParameters	SpawnParam;
	//SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//mSpawnObject = GetWorld()->SpawnActor<AFadeFloor>(mSpawnClass, GetActorLocation(), GetActorRotation(), SpawnParam);

	//mSpawnObject->mSetSpawnPoint(this);
	//mSpawnObject->mSetScale3D(mScale3D);
	//mSpawnObject->mSetMaterial(mMaterial);
}

void AMoveFloor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
