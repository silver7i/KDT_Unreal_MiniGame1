// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FAKERUNNER_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	mMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	mMoveDir;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
