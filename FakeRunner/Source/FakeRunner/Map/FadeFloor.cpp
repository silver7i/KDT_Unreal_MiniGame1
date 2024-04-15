// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeFloor.h"
#include "FloorSpawnPoint.h"

// Sets default values
AFadeFloor::AFadeFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//SetRootComponent(mRoot);
	mFloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	SetRootComponent(mFloorMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Cube.Succeeded())
	{
		mFloorMesh->SetStaticMesh(Cube.Object);
	}

	mFloorMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	mFloorMesh->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));

	mFloorMesh->bVisualizeComponent = true;

	mSpawnPoint = nullptr;
}

// Called when the game starts or when spawned
void AFadeFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFadeFloor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (mSpawnPoint)
	{
		mSpawnPoint->ClearSpawnObject();
	}
}

// Called every frame
void AFadeFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mDeleteEnable)
	{
		mDeleteTime += DeltaTime;
		if (mDeleteTime > mDeleteDuration)
		{
			Destroy();
		}
	}

}

void AFadeFloor::DeleteFloor()
{
	mDeleteEnable = true;
}


