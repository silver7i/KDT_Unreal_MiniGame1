// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerTrigger.h"
#include "TransparentFloor.generated.h"

/**
 * 
 */
UCLASS()
class FAKERUNNER_API ATransparentFloor : public APlayerTrigger
{
	GENERATED_BODY()

public:
	ATransparentFloor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mFloorMesh;

	TArray<UMaterialInstanceDynamic*>	mMaterialArray;

	bool	mOpacityEnable;
	float	mOpacityTime;

	UPROPERTY(EditAnywhere)
	float	mOpacityDuration;

	float	mParamEnable;
	float	mParamMask;
	float	mParamGlow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", meta = (MakeEditWidget = true))
	uint32	bMoveEnable : 1;

	bool	mMoveEnable = false;
	FVector mStartLocation;
	FVector mGlobalEndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	FVector	mEndLocation;

	UPROPERTY(EditAnywhere, Category = "Move")
	float	mMoveSpeed = 500.f;
	float	mMoveDuration = 0.5f;
	float	mMoveTime = 0.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

};
