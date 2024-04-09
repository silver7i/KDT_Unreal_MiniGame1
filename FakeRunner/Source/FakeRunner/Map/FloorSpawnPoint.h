// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerTrigger.h"
#include "FloorSpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class FAKERUNNER_API AFloorSpawnPoint : public APlayerTrigger
{
	GENERATED_BODY()

public:
	AFloorSpawnPoint();

protected:
	// 이 포인트에서 생성할 클래스 타입을 가지고 있게 한다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AFadeFloor>	mSpawnClass;

	// 위의 클래스를 이용해서
	// 실제로 생성된 객체의 메모리 주소를 저장해둔다.
	class AFadeFloor* mSpawnObject;

	// 객체가 제거되고 지정된 시간 이후에
	// 다시 생성하게 하기위한 변수
	float	mSpawnTime = 5.f;

	// 생성을 위해 시간을 계산하기 위한 변수
	float	mAccTime;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Spawn();

public:
	void ClearSpawnObject();

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	
};
