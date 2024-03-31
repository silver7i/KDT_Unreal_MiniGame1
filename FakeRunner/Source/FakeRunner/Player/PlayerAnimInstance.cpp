// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"
#include "MainPlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mCanJump = true;

	mAnimType = EPlayerAnimType::Idle;

	mAdditiveAlpha = 0.f;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

// 이 함수는 매 프레임마다 동작한다.
void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 체크한다.
	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();

		if (IsValid(Movement))
		{
			// 속도 벡터(Velocity)의 크기(Length)를 구해서
			// 이동속도로 사용한다.
			mMoveSpeed = Movement->Velocity.Length();

			// 속도의 비율을 구한다.
			mMoveSpeed /= Movement->MaxWalkSpeed;

			// IsMovingOnGround() : 땅을 밝고 있는지 판단해주는 함수
			mOnGround = Movement->IsMovingOnGround();
			if (!mOnGround && mAnimType != EPlayerAnimType::Jump && mAnimType != EPlayerAnimType::Fall)
			{
				mAnimType = EPlayerAnimType::Fall;
			}
		}

		// 이 애님인스턴스를 가지고 있는 캐릭터로부터 해당 캐릭터를 컨트롤 하고 있는
		// 플레이어 컨트롤러를 얻어온다.
		AMainPlayerController* Controller = PlayerCharacter->GetController<AMainPlayerController>();

		// 위에서 얻어온 컨트롤러가 유효하면 GetMoveDir()함수의 return 값으로
		// mMoveDir 값을 얻어온다. 
		if (IsValid(Controller))
		{
			mMoveDir = Controller->GetMoveDir();
		}
	}
}

void UPlayerAnimInstance::PlayJump()
{
	mCanJump = false;

	mAnimType = EPlayerAnimType::Jump;

	// 점프 리커버리 몽타주가 재생되고 있다면 재생을 중지한다.
	if (Montage_IsPlaying(mJumpRecoveryAdditiveMontage))
	{
		Montage_Stop(0.1f, mJumpRecoveryAdditiveMontage);
		mAdditiveAlpha = 0.f;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Montage_Stop"));

	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("PlayJump"));

}

void UPlayerAnimInstance::AnimNotify_TransitionFall()
{
	mAnimType = EPlayerAnimType::Fall;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("AnimNotify_TransitionFall"));

}

void UPlayerAnimInstance::AnimNotify_FallEnd()
{
	mAnimType = EPlayerAnimType::Idle;

	// 리커버리 Additive를 적용하기 위해 값을 1로 변경
	mAdditiveAlpha = 1.f;

	// 리커버리 동작 재생
	if (!Montage_IsPlaying(mJumpRecoveryAdditiveMontage))
	{
		Montage_SetPosition(mJumpRecoveryAdditiveMontage, 0.f);

		Montage_Play(mJumpRecoveryAdditiveMontage);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Montage_Play"));
	}
	// 다시 점프 가능한 상태로 변경
	mCanJump = true;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("AnimNotify_FallEnd"));

}

void UPlayerAnimInstance::AnimNotify_JumpRecoveryEnd()
{
	// 점프 리커버리 동작이 모두 완료가 되었다면
	// 더이상 Additive를 적용할 필요가 없다.
	mAdditiveAlpha = 0.f;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("AnimNotify_JumpRecoveryEnd"));
}
