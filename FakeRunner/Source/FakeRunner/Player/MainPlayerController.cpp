// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Data/Input/BasicInputDataConfig.h"
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
	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);

	// 좌 우 이동
	ControlledPawn->AddMovementInput(RightVector, ActionValue.X);
}

