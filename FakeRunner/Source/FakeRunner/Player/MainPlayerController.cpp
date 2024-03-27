// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Data/Input/BasicInputDataConfig.h"
#include "time.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// BasicInputDataConfig의 CDO객체를 얻어온 다음에
	// CDO객체에 있는 DefaultContext를 사용할 것이다.
	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	Subsystem->AddMappingContext(BasicInputDataConfig->mDefaultContext, 0);
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	// ensure은 내부의 판별식이 false일 때 작용한다.
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(BasicInputDataConfig->mMove, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
}

void AMainPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();

	const FRotator Rotation = K2_GetActorRotation();	//  K2_GetActorRotation() : RootComponent 회전을 반환
	const FRotator YawRotation = FRotator(0.0, Rotation.Yaw, 0.0);	// Pitch(y), Yaw(z), Roll(x)
	const FVector ForwardVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	// 앞 뒤 이동
	// ActionValue.Y는 앞일때 1, 뒤일때 -1, 움직이지 않을 경우 0이 들어온다.
	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);

	// 좌 우 이동
	// ActionValue.X는 오른쪽일때 1, 왼쪽일때 - 1, 움직이지 않을 경우 0이 들어온다
	ControlledPawn->AddMovementInput(RightVector, ActionValue.X);

	// 이동 방향을 저장한다.
	// 블렌드 스페이스에서 지정해 놨던 -180~180 각도별 방향 
	mMoveDir = ActionValue.X * 90.f;

	// 앞으로 이동할 경우
	if (ActionValue.Y > 0.f)
	{
		// 전방 왼쪽 대각선 방향
		if (ActionValue.X < 0.f)
		{
			mMoveDir = -45.f;
		}

		// 전방 오른쪽 대각선 방향
		else if (ActionValue.X > 0.f)
		{
			mMoveDir = 45.f;
		}
	}
	// 뒤로 이동할 경우
	else if (ActionValue.Y < 0.f)
	{
		// 후방 왼쪽 대각선 방향
		if (ActionValue.X < 0.f)
		{
			mMoveDir = -135.f;
		}
		// 후방 오른쪽 대각선 방향
		else if (ActionValue.X > 0.f)
		{
			mMoveDir = 135.f;
		}
		// 후방
		else
			mMoveDir = 180.f;
	}
	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("%f"), YawRotation.Yaw));
	// else if (ActionValue.Y == 0)
	//		if (ActionValue.X == 0 )	---> mMovedir == 0		전방
	//		if (ActionValue.X == -1)	---> mMovedir == -90.f	왼쪽
	//		if (ActionValue.X == 1 )	---> mMovedir == 90.f	오른쪽
}