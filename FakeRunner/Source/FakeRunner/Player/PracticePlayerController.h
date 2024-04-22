// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MainPlayerController.h"
#include "PracticePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FAKERUNNER_API APracticePlayerController : public AMainPlayerController
{
	GENERATED_BODY()

public:
	APracticePlayerController();

private:
	TSubclassOf<UUserWidget>	mManualWidgetClass;
	UUserWidget* mManualWidget;

protected:
	virtual void BeginPlay() override;
	
};
