// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "MainPlayerController.generated.h"


#define CAMERA_ARM_PITCH_MIN	-60.f
#define CAMERA_ARM_PITCH_MAX	0.f
/**
 * 
 */
UCLASS()
class FAKERUNNER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	float	mMoveDir;

public:
	float GetMoveDir()
	{
		return mMoveDir;
	}

public:
	FRotator CameraArmRotation;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnMouse(const FInputActionValue& InputActionValue);
	void OnMove(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
};

