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
	USceneComponent* mRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mFloorCube;

	class AFloorSpawnPoint* mSpawnPoint;

	bool	mDeleteEnable = false;
	float	mDeleteTime = 0.f;
	float	mDeleteDuration = 1.f;

public:
	void SetSpawnPoint(class AFloorSpawnPoint* Point)
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

	void DeleteFloor();

};
