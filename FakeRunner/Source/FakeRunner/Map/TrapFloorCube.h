// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerTrigger.h"
#include "TrapFloorCube.generated.h"

/**
 * 
 */
UCLASS()
class FAKERUNNER_API ATrapFloorCube : public APlayerTrigger
{
	GENERATED_BODY()

public:
	ATrapFloorCube();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mFloorCube;

	bool	mHit = false;
	bool	mSpawnEnable = false;
	float	mHitTime = 0.f;

	UPROPERTY(EditAnywhere)
	float	mDeleteDuration = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Spawn();

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};
