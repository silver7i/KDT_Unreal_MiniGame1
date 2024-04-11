// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeFloor.h"
#include "FloorSpawnPoint.h"

// Sets default values
AFadeFloor::AFadeFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mFloorCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	mFloorCube->SetupAttachment(mRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Script/Engine.StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	if (Cube.Succeeded())
	{
		mFloorCube->SetStaticMesh(Cube.Object);
	}

	mFloorCube->SetRelativeLocation(FVector(0.f, 0.f, -130.f));
	mFloorCube->SetRelativeScale3D(FVector(1.175f, 1.175f, 1.01f));

	mRoot->bVisualizeComponent = true;

	mSpawnPoint = nullptr;
}

// Called when the game starts or when spawned
void AFadeFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFadeFloor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("EndPlay"));

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



