// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PracticePlayerController.h"
#include "Blueprint/UserWidget.h"

APracticePlayerController::APracticePlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>
		ManualWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Player/UI/UI_Manual.UI_Manual_C'"));

	if (ManualWidgetClass.Succeeded())
		mManualWidgetClass = ManualWidgetClass.Class;
}

void APracticePlayerController::BeginPlay()
{
	Super::BeginPlay();

	mManualWidget = CreateWidget<UUserWidget>(GetWorld(), mManualWidgetClass);
	mManualWidget->AddToViewport();
}
