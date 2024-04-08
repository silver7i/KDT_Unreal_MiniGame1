// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Map/PlayerTrigger.h"
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

	bool	mHtiEnable = false;
	float	mHitTime = 0.f;
	float	mDeleteDuration = 0.3f;

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
