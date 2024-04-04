// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class FAKERUNNER_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	USceneComponent* mRoot;

//#if WITH_EDITORONLY_DATA
//	UArrowComponent* mArror;
//#endif

	// 이 포인트에서 생성하려는 클래스 타입을 가지고 있게 한다.
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerCharacter> mSpawnClass;

	// 위의 클래스를 이용해서
	// 실제로 생성된 객체의 메모리 주소를 저장해둔다.
	class APlayerCharacter* mSpawnPlayer;

	// 실제 생성된 객체가 제거되고
	// 지정된 시간 이후에 다시 생성하게 하기 위한 변수
	UPROPERTY(EditAnywhere)
	float mSpawnTime;

	// 생성을 위한 시간을 계산하기 위한 변수
	float mAccTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
