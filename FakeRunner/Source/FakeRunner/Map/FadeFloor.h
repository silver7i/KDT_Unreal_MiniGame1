// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "FadeFloor.generated.h"

UCLASS()
class FAKERUNNER_API AFadeFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFadeFloor();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mFloorMesh;

	class AFloorSpawnPoint* mSpawnPoint;

	bool	mDeleteEnable = false;
	float	mDeleteTime = 0.f;

	UPROPERTY(EditAnywhere)
	float	mDeleteDuration = 0.2f;

public:
	void mSetSpawnPoint(class AFloorSpawnPoint* Point)
	{
		mSpawnPoint = Point;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DeleteFloor(float DurationTime);

	void mSetMaterial(UMaterialInstance* Material)
	{
		mFloorMesh->SetMaterial(0, Material);
	}

	void mSetScale3D(FVector Scale)
	{
		mFloorMesh->SetRelativeScale3D(Scale);
	}
};
