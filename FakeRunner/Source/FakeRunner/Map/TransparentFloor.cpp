// Fill out your copyright notice in the Description page of Project Settings.


#include "TransparentFloor.h"

ATransparentFloor::ATransparentFloor()
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

void ATransparentFloor::BeginPlay()
{
	Super::BeginPlay();
	mTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATransparentFloor::BeginOverlap);
}

void ATransparentFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mHit)
	{
		mHitTime += DeltaTime;
		if (mHitTime > mDeleteDuration)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("mHitTime : %f"), mHitTime));

			mHitTime = 0.f;
		}
	}
}

void ATransparentFloor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Hit"));
	mHit = true;
	mHitTime = 0.f;
}



