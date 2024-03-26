// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

// 이 함수는 매 프레임마다 동작한다.
void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* OwnerPawn = Cast<APlayerCharacter>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 체크한다.
	if (IsValid(OwnerPawn))
	{
		UCharacterMovementComponent* Movement = OwnerPawn->GetCharacterMovement();

		if (IsValid(Movement))
		{
			// 속도 벡터(Velocity)의 크기(Length)를 구해서
			// 이동속도로 사용한다.
			mMoveSpeed = Movement->Velocity.Length();

			// 속도의 비율을 구한다.
			mMoveSpeed /= Movement->MaxWalkSpeed;
		}
	}
}
