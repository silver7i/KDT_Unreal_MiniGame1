// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/TrapFloorCube.h"

ATrapFloorCube::ATrapFloorCube()
{
	mTrigger->SetCollisionProfileName(TEXT("PlayerTrigger"));

	mTrigger->InitBoxExtent(FVector(130.f, 130.f, 130.f));

	mFloorCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	mFloorCube->SetupAttachment(mTrigger);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	if (Cube.Succeeded())
	{
		mFloorCube->SetStaticMesh(Cube.Object);
	}

	mFloorCube->SetRelativeLocation(FVector(0.f, 0.f, -130.f));
	mFloorCube->SetRelativeScale3D(FVector(1.01f, 1.01f, 1.01f));
}

void ATrapFloorCube::BeginPlay()
{
	Super::ReceiveBeginPlay();
	mTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATrapFloorCube::BeginOverlap);
}

void ATrapFloorCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrapFloorCube::Spawn()
{

}

void ATrapFloorCube::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

