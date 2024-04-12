// Fill out your copyright notice in the Description page of Project Settings.


#include "TransparentFloor.h"

ATransparentFloor::ATransparentFloor()
{
	mTrigger->SetCollisionProfileName(TEXT("PlayerTrigger"));

	mTrigger->InitBoxExtent(FVector(150.f, 150.f, 52.f));

	mFloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	mFloorMesh->SetupAttachment(mTrigger);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (Cube.Succeeded())
	{
		mFloorMesh->SetStaticMesh(Cube.Object);
	}

	mFloorMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	mFloorMesh->SetRelativeScale3D(FVector(3.f, 3.f, 1.f));

	mOpacityEnable = true;
	mOpacityTime = 0;
	mOpacityDuration = 5.f;
}

void ATransparentFloor::BeginPlay()
{
	Super::BeginPlay();
	mTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATransparentFloor::BeginOverlap);
	mTrigger->OnComponentEndOverlap.AddDynamic(this, &ATransparentFloor::EndOverlap);


	// 메시가 가지고 있는 머티리얼이 몇개인지 얻어온다.
	int32 ElementCount = mFloorMesh->GetNumMaterials();

	for (int32 i = 0; i < ElementCount; ++i)
	{
		// 다이나믹 머테리얼 인스턴스를 생성해서 머테리얼 배열에 넣어준다.
		UMaterialInstanceDynamic* Mtrl = mFloorMesh->CreateDynamicMaterialInstance(i);
		mMaterialArray.Add(Mtrl);
	}
}

void ATransparentFloor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("ATransparentFloor OnConstruction"));

	//// 메시가 가지고 있는 머티리얼이 몇개인지 얻어온다.
	//int32 ElementCount = mFloorMesh->GetNumMaterials();

	//for (int32 i = 0; i < ElementCount; ++i)
	//{
	//	// 다이나믹 머테리얼 인스턴스를 생성해서 머테리얼 배열에 넣어준다.
	//	UMaterialInstanceDynamic* Mtrl = mFloorMesh->CreateDynamicMaterialInstance(i);
	//	mMaterialArray.Add(Mtrl);
	//}
}

void ATransparentFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!mOpacityEnable)
	{
		mOpacityTime += DeltaTime;
		if (mOpacityTime > mOpacityDuration && !mMaterialArray.IsEmpty())
		{
			mOpacityEnable = true;
			mOpacityTime = 0.f;

			for (auto Mtrl : mMaterialArray)
			{
				Mtrl->SetScalarParameterValue(TEXT("Opacity"), 0.f);
				Mtrl->SetScalarParameterValue(TEXT("OverlapEnable"), 0.f);
			}
		}
	}

}

void ATransparentFloor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Hit"));

	mOpacityEnable = true;
	mOpacityTime = 0.f;

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("mMaterialArray : %d"), mMaterialArray.Num()));

	if (!mMaterialArray.IsEmpty())
	{
		for (auto Mtrl : mMaterialArray)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,TEXT("Opacity"));

			Mtrl->SetScalarParameterValue(TEXT("Opacity"), 0.2f);
			Mtrl->SetScalarParameterValue(TEXT("OverlapEnable"), 1.f);
		}
	}
}

void ATransparentFloor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	mOpacityEnable = false;
}


