// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Idle,
	Jump,
	Fall
};

UCLASS()
class FAKERUNNER_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerAnimType mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	mOnGround;

	bool	mCanJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* mJumpRecoveryAdditiveMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	mAdditiveAlpha;


public:
	UPlayerAnimInstance();

public:
	void SetAnimType(EPlayerAnimType Type)
	{
		mAnimType = Type;
	}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	mMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	mMoveDir;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void PlayJump();

	UFUNCTION()
	void AnimNotify_TransitionFall();

	UFUNCTION()
	void AnimNotify_FallEnd();

	UFUNCTION()
	void AnimNotify_JumpRecoveryEnd();
};
