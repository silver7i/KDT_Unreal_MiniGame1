// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "BasicInputDataConfig.generated.h"

UCLASS()
class UBasicInputDataConfig : public UObject
{
	GENERATED_BODY()

public:
	UBasicInputDataConfig();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* mDefaultContext = nullptr;

public:
	UInputAction* mMouse = nullptr;
	UInputAction* mMove = nullptr;
	UInputAction* mJump = nullptr;
	
};
