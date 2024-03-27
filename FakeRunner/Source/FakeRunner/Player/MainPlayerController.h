// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "MainPlayerController.generated.h"

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
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
};

