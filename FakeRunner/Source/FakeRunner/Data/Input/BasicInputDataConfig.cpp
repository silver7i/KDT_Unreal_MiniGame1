// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicInputDataConfig.h"

UBasicInputDataConfig::UBasicInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Blueprints/Player/Input/IMC_Default.IMC_Default'") };
		if (Asset.Succeeded())
		{
			mDefaultContext = Asset.Object;
		}
	}

	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Blueprints/Player/Input/IA_Move.IA_Move'")};
		if(Asset.Succeeded())
		{
			mMove = Asset.Object;
		}
	}
}
